-- Must search by movies.id because the titles themselves aren't unique!
-- SELECT people.id is important in case of similar names.
-- Finally, you need SELECT DISTINCT name because the same actors could have been in multiple movies with Kevin Bacon.

SELECT DISTINCT name
FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE NOT name = "Kevin Bacon" AND people.id IN
    (
    SELECT people.id
    FROM people
    JOIN stars ON stars.person_id = people.id
    JOIN movies ON movies.id = stars.movie_id
    WHERE movies.id IN
        (
        SELECT movies.id
        FROM movies
        JOIN stars ON stars.movie_id = movies.id
        JOIN people ON people.id = stars.person_id
        WHERE people.name = "Kevin Bacon" and birth = "1958"
        )
    );

-- Better solution with MUCH shorter runtime:
-- 1. Get ids of movies where Kevin Bacon starred in.
-- 2. Find ids of people that also starred in those movies.
-- 3. Find the names of the ids and exclude Kevin Bacon.

-- SELECT DISTINCT name
-- FROM people
-- WHERE name != 'Kevin Bacon'
-- AND id IN
--    (
--    SELECT person_id
--    FROM stars
--    WHERE movie_id IN
--        (
--        SELECT movie_id
--        FROM stars
--        WHERE person_id IN
--            (
--            SELECT id
--            FROM people
--            WHERE name = 'Kevin Bacon' and birth = 1958
--            )
--        )
--    );