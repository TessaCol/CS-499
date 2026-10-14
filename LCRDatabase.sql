SELECT
    g.game_id,
    p.player_name AS winner
FROM Games g
JOIN Players p
    ON g.winner_id = p.player_id
WHERE g.game_id = 1;