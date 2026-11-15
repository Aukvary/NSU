-- 2.1
WITH airplane_seats AS (
    SELECT
        airplane_code,
        COUNT(*) AS seats_count
    FROM
        seats
    GROUP BY
        airplane_code
)
SELECT
    r.route_no,
    r.airplane_code,
    aps.seats_count,
    COUNT(f.flight_id) AS flights_count
FROM
    routes r
    JOIN airports dep ON r.departure_airport = dep.airport_code
    JOIN airports arr ON r.arrival_airport = arr.airport_code
    JOIN airplane_seats aps ON r.airplane_code = aps.airplane_code
    LEFT JOIN flights f ON r.route_no = f.route_no
        AND f.scheduled_departure >= bookings.now() - interval '1 month'
WHERE
    r.validity @> bookings.now()
    AND dep.timezone = 'Asia/Shanghai'
    AND arr.timezone = 'Asia/Shanghai'
GROUP BY
    r.route_no,
    r.airplane_code,
    aps.seats_count
ORDER BY
    flights_count DESC;

-- 2.2
SELECT
    r.*
FROM
    routes r
    JOIN airplanes a ON r.airplane_code = a.airplane_code
WHERE
    a.range BETWEEN 5000 AND 10000
    AND a.speed >= 800;

-- 2.3
WITH route_stats AS (
    SELECT
        r.route_no,
        r.validity,
        COUNT(f.flight_id) AS total_flights,
        COUNT(f.flight_id) FILTER (WHERE f.status = 'Cancelled') AS cancelled_flights,
        ROUND(COUNT(f.flight_id) FILTER (WHERE f.status = 'Cancelled') * 100.0 / COUNT(f.flight_id), 2) AS cancelled_pct
    FROM
        routes r
        JOIN flights f ON r.route_no = f.route_no
            AND r.validity @> f.scheduled_departure
    GROUP BY
        r.route_no,
        r.validity
    HAVING
        COUNT(f.flight_id) FILTER (WHERE f.status = 'Cancelled') * 100.0 / COUNT(f.flight_id) >= 20
)
SELECT
    r.*,
    rs.total_flights,
    rs.cancelled_flights,
    rs.cancelled_pct
FROM
    routes r
    JOIN route_stats rs ON r.route_no = rs.route_no
        AND r.validity = rs.validity
    ORDER BY
        rs.cancelled_pct DESC;

-- 2.4
WITH lon_bounds AS (
    SELECT
        MIN(coordinates[0]) FILTER (WHERE city IN ('Novosibirsk', 'Новосибирск')) AS min_lon,
        MAX(coordinates[0]) FILTER (WHERE city IN ('Vladivostok', 'Владивосток')) AS max_lon
    FROM
        airports
)
SELECT
    a.airport_code,
    COUNT(r.route_no) AS routes_count
FROM
    airports a
    CROSS JOIN lon_bounds lb
    LEFT JOIN routes r ON a.airport_code = r.departure_airport
WHERE
    a.country IN ('Russia', 'Россия')
    AND a.coordinates[0] BETWEEN lb.min_lon AND lb.max_lon
GROUP BY
    a.airport_code
ORDER BY
    routes_count DESC;

-- 2.5
WITH airplane_seats AS (
    SELECT
        airplane_code,
        COUNT(*) AS seats_count
    FROM
        seats
    GROUP BY
        airplane_code
),
flight_sold AS (
    SELECT
        flight_id,
        COUNT(*) AS sold_count
    FROM
        segments
    GROUP BY
        flight_id
)
SELECT
    r.route_no,
    EXTRACT(ISODOW FROM f.scheduled_departure)::INTEGER AS day_of_week,
    COALESCE(SUM(fs.sold_count), 0) AS total_sold,
    SUM(aps.seats_count) AS total_seats,
    ROUND(COALESCE(SUM(fs.sold_count), 0) * 100.0 / SUM(aps.seats_count), 2) AS occupancy_pct
FROM
    flights f
    JOIN routes r ON f.route_no = r.route_no
        AND r.validity @> f.scheduled_departure
    JOIN airplane_seats aps ON r.airplane_code = aps.airplane_code
    LEFT JOIN flight_sold fs ON f.flight_id = fs.flight_id
WHERE
    f.status = 'Arrived'
    AND f.scheduled_departure BETWEEN bookings.now() - interval '1 month' AND bookings.now()
GROUP BY
    r.route_no,
    day_of_week
ORDER BY
    r.route_no,
    day_of_week;

