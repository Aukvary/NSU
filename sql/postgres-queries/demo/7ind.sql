-- 2.1
SELECT
    r.departure_airport,
    COUNT(f.flight_id) AS total_flights,
    COUNT(*) FILTER (WHERE f.status = 'Cancelled') AS cancelled_flights
FROM
    routes r
    LEFT JOIN flights f ON r.route_no = f.route_no
GROUP BY
    r.departure_airport;

-- 2.2
SELECT
    ad.timezone,
    AVG(s.price) AS avg_price,
    SUM(s.price) AS total_revenue
FROM
    airports_data ad
    JOIN routes r ON ad.airport_code = r.departure_airport
    JOIN flights f ON r.route_no = f.route_no
    JOIN segments s ON f.flight_id = s.flight_id
WHERE
    f.status = 'Arrived'
GROUP BY
    ad.timezone
ORDER BY
    total_revenue DESC;

-- 2.3
SELECT
    r.departure_airport,
    s.fare_conditions,
    MIN(s.price) AS min_price,
    MAX(s.price) AS max_price,
    COUNT(*) AS segments_count
FROM
    routes r
    JOIN flights f ON r.route_no = f.route_no
    JOIN segments s ON f.flight_id = s.flight_id
GROUP BY
    r.departure_airport,
    s.fare_conditions
ORDER BY
    r.departure_airport,
    s.fare_conditions;

-- 2.4
WITH seat_counts AS (
    SELECT
        airplane_code,
        COUNT(seat_no) AS seats_count
    FROM
        seats
    GROUP BY
        airplane_code
)
SELECT
    sc.airplane_code,
    sc.seats_count,
    COUNT(bp.ticket_no) AS boarding_passes_count,
    COUNT(DISTINCT bp.flight_id) AS unique_flights_count
FROM
    seat_counts sc
    JOIN routes r ON sc.airplane_code = r.airplane_code
    JOIN flights f ON r.route_no = f.route_no
    JOIN boarding_passes bp ON f.flight_id = bp.flight_id
GROUP BY
    sc.airplane_code,
    sc.seats_count
HAVING
    COUNT(bp.ticket_no) > 100
ORDER BY
    boarding_passes_count DESC;

-- 2.5
SELECT
    ticket_no,
    seat_no,
    boarding_no,
    LAG(boarding_no) OVER (ORDER BY boarding_no) AS prev_boarding_no,
    LEAD(boarding_no) OVER (ORDER BY boarding_no) AS next_boarding_no
FROM
    boarding_passes
WHERE
    flight_id = 1
ORDER BY
    boarding_no;

-- 2.6
WITH airport_airplanes AS (
    SELECT DISTINCT
        departure_airport,
        airplane_code
    FROM
        routes
),
seat_counts AS (
    SELECT
        airplane_code,
        COUNT(*) AS seats_count
    FROM
        seats
    GROUP BY
        airplane_code
)
SELECT
    aa.departure_airport,
    aa.airplane_code,
    ad.range,
    sc.seats_count,
    FIRST_VALUE(sc.seats_count) OVER (PARTITION BY aa.departure_airport ORDER BY ad.range, aa.airplane_code ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS seats_at_min_range,
    LAST_VALUE(sc.seats_count) OVER (PARTITION BY aa.departure_airport ORDER BY ad.range, aa.airplane_code ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS seats_at_max_range
FROM
    airport_airplanes aa
    JOIN airplanes_data ad ON aa.airplane_code = ad.airplane_code
    JOIN seat_counts sc ON aa.airplane_code = sc.airplane_code
ORDER BY
    aa.departure_airport,
    ad.range;

-- 2.7
SELECT
    airplane_code,
    speed,
    RANGE,
    MIN(speed) OVER () AS min_speed,
    MAX(speed) OVER () AS max_speed,
    speed - MIN(speed) OVER () AS speed_diff_from_min
FROM
    airplanes_data
ORDER BY
    speed;

-- 2.8
SELECT
    airplane_code,
    RANGE,
    ROUND(RANGE::NUMERIC, -3) AS rounded_range,
    RANK() OVER (ORDER BY ROUND(RANGE::NUMERIC, -3) DESC) AS range_rank,
    DENSE_RANK() OVER (ORDER BY ROUND(RANGE::NUMERIC, -3) DESC) AS dense_rank,
    ROW_NUMBER() OVER (ORDER BY ROUND(RANGE::NUMERIC, -3) DESC) AS row_num
FROM
    airplanes_data
ORDER BY
    range_rank,
    row_num;

