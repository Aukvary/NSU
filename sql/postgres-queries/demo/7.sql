-- 1.1
SELECT
    r.airplane_code,
    COUNT(f.flight_id) AS total_flights,
    COUNT(*) FILTER (WHERE f.status IN ('Delayed', 'Cancelled')) AS problematic_flights
FROM
    routes r
    LEFT JOIN flights f ON r.route_no = f.route_no
GROUP BY
    r.airplane_code;

-- 1.2
SELECT
    r.departure_airport,
    AVG(s.price) AS avg_price,
    SUM(s.price) AS total_revenue
FROM
    routes r
    JOIN flights f ON r.route_no = f.route_no
    JOIN segments s ON f.flight_id = s.flight_id
WHERE
    f.status = 'Arrived'
GROUP BY
    r.departure_airport
ORDER BY
    total_revenue DESC;

-- 1.3
SELECT
    a.airplane_code,
    s.fare_conditions,
    MIN(s.price) AS min_price,
    MAX(s.price) AS max_price,
    MAX(s.price) - MIN(s.price) AS price_diff
FROM
    airplanes_data a
    JOIN routes r ON a.airplane_code = r.airplane_code
    JOIN flights f ON r.route_no = f.route_no
    JOIN segments s ON f.flight_id = s.flight_id
GROUP BY
    a.airplane_code,
    s.fare_conditions
ORDER BY
    a.airplane_code,
    s.fare_conditions;

-- 1.4
SELECT
    b.book_ref,
    b.book_date,
    b.total_amount,
    COUNT(t.ticket_no) AS tickets_count,
    COUNT(DISTINCT t.passenger_id) AS unique_passengers
FROM
    bookings b
    JOIN tickets t ON b.book_ref = t.book_ref
WHERE
    b.total_amount > 100000
GROUP BY
    b.book_ref,
    b.book_date,
    b.total_amount
HAVING
    COUNT(t.ticket_no) > 3
ORDER BY
    b.total_amount DESC;

-- 1.5
SELECT
    route_no,
    flight_id,
    scheduled_departure,
    LAG(scheduled_departure) OVER (PARTITION BY route_no ORDER BY scheduled_departure) AS prev_departure,
    LEAD(scheduled_departure) OVER (PARTITION BY route_no ORDER BY scheduled_departure) AS next_departure
FROM
    flights
ORDER BY
    route_no,
    scheduled_departure;

-- 1.6
SELECT
    f.route_no,
    f.flight_id,
    f.scheduled_departure,
    s.price,
    FIRST_VALUE(s.price) OVER (PARTITION BY f.route_no ORDER BY f.scheduled_departure, f.flight_id, s.ticket_no ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS first_price_of_route,
    LAST_VALUE(s.price) OVER (PARTITION BY f.route_no ORDER BY f.scheduled_departure, f.flight_id, s.ticket_no ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS last_price_of_route
FROM
    flights f
    JOIN segments s ON f.flight_id = s.flight_id
WHERE
    f.status = 'Arrived'
ORDER BY
    f.route_no,
    f.scheduled_departure;

-- 1.7
SELECT
    route_no,
    flight_id,
    scheduled_departure,
    MIN(scheduled_departure) OVER (PARTITION BY route_no) AS min_departure_on_route,
    MAX(scheduled_departure) OVER (PARTITION BY route_no) AS max_departure_on_route,
    EXTRACT(EPOCH FROM (scheduled_departure - MIN(scheduled_departure) OVER (PARTITION BY route_no))) / 3600 AS diff_from_min
FROM
    flights
WHERE
    status = 'Arrived'
ORDER BY
    route_no,
    scheduled_departure;

-- 1.8
SELECT
    r.departure_airport,
    AVG(s.price) AS avg_price,
    ROUND(AVG(s.price), -2) AS rounded_price,
    RANK() OVER (ORDER BY ROUND(AVG(s.price), -2) DESC) AS price_rank,
    DENSE_RANK() OVER (ORDER BY ROUND(AVG(s.price), -2) DESC) AS dense_rank,
    ROW_NUMBER() OVER (ORDER BY ROUND(AVG(s.price), -2) DESC) AS row_num
FROM
    routes r
    JOIN flights f ON r.route_no = f.route_no
    JOIN segments s ON f.flight_id = s.flight_id
GROUP BY
    r.departure_airport
ORDER BY
    price_rank,
    row_num;

