-- 1.1
SELECT
    airplane_code,
    model,
    make_interval(secs => round(RANGE * 3600.0 / speed)) AS max_duration
FROM
    airplanes
WHERE
    RANGE::NUMERIC / speed > (
        SELECT
            AVG(RANGE::NUMERIC / speed)
        FROM
            airplanes)
ORDER BY
    max_duration;

-- 1.2
SELECT
    r.route_no,
    r.airplane_code,
    COUNT(f.flight_id) AS flights_count
FROM
    routes r
    JOIN airports dep ON r.departure_airport = dep.airport_code
    JOIN airports arr ON r.arrival_airport = arr.airport_code
    LEFT JOIN flights f ON r.route_no = f.route_no
        AND f.scheduled_departure >= bookings.now() - interval '1 month'
WHERE
    r.validity @> bookings.now()
    AND dep.timezone = 'Asia/Shanghai'
    AND arr.timezone = 'Asia/Shanghai'
GROUP BY
    r.route_no,
    r.airplane_code
ORDER BY
    flights_count DESC;

-- 1.3
SELECT
    *
FROM
    airplanes
WHERE (RANGE, speed) = (
    SELECT
        MIN(RANGE),
        MIN(speed)
    FROM
        airplanes);

-- 1.4
WITH fleet_avg AS (
    SELECT
        AVG(RANGE) AS avg_range,
        AVG(speed) AS avg_speed
    FROM
        airplanes
)
SELECT
    a.*
FROM
    airplanes a
    CROSS JOIN fleet_avg f
WHERE
    ABS(a.range - f.avg_range) <= 0.3 * f.avg_range
    AND ABS(a.speed - f.avg_speed) <= 0.3 * f.avg_speed;

-- 1.5
SELECT
    f.*
FROM
    flights f
    JOIN segments s ON f.flight_id = s.flight_id
WHERE
    f.status = 'Scheduled'
GROUP BY
    f.flight_id
HAVING
    COUNT(*) FILTER (WHERE s.fare_conditions = 'Economy') = 0
    AND COUNT(*) FILTER (WHERE s.fare_conditions = 'Business') >= 2;

-- 1.6
WITH seat_counts AS (
    SELECT
        airplane_code,
        COUNT(*) AS total_seats,
        COUNT(*) FILTER (WHERE fare_conditions = 'Economy') AS eco_seats,
        COUNT(*) FILTER (WHERE fare_conditions = 'Comfort') AS comf_seats,
        COUNT(*) FILTER (WHERE fare_conditions = 'Business') AS bus_seats
    FROM
        seats
    GROUP BY
        airplane_code
),
target_flights AS (
    SELECT
        f.flight_id,
        f.scheduled_departure,
        r.airplane_code
    FROM
        flights f
        JOIN routes r ON f.route_no = r.route_no
            AND r.validity @> f.scheduled_departure
    WHERE
        f.status = 'Scheduled'
        AND f.scheduled_departure BETWEEN bookings.now()
        AND bookings.now() + interval '2 days'
),
sold_counts AS (
    SELECT
        tf.flight_id,
        COUNT(s.ticket_no) AS total_sold,
        COUNT(s.ticket_no) FILTER (WHERE s.fare_conditions = 'Economy') AS eco_sold,
        COUNT(s.ticket_no) FILTER (WHERE s.fare_conditions = 'Comfort') AS comf_sold,
        COUNT(s.ticket_no) FILTER (WHERE s.fare_conditions = 'Business') AS bus_sold
    FROM
        target_flights tf
        LEFT JOIN segments s ON tf.flight_id = s.flight_id
    GROUP BY
        tf.flight_id
)
SELECT
    tf.flight_id,
    tf.scheduled_departure,
    NULLIF (sc.eco_seats, 0) - so.eco_sold AS free_economy,
    NULLIF (sc.comf_seats, 0) - so.comf_sold AS free_comfort,
    NULLIF (sc.bus_seats, 0) - so.bus_sold AS free_business,
    ROUND(so.total_sold * 100.0 / NULLIF (sc.total_seats, 0), 2) AS total_sold_pct,
    ROUND(so.eco_sold * 100.0 / NULLIF (sc.eco_seats, 0), 2) AS economy_sold_pct,
    ROUND(so.comf_sold * 100.0 / NULLIF (sc.comf_seats, 0), 2) AS comfort_sold_pct,
    ROUND(so.bus_sold * 100.0 / NULLIF (sc.bus_seats, 0), 2) AS business_sold_pct
FROM
    target_flights tf
    JOIN seat_counts sc ON tf.airplane_code = sc.airplane_code
    JOIN sold_counts so ON tf.flight_id = so.flight_id
ORDER BY
    total_sold_pct DESC;

