SELECT
	count(*)
FROM
	(
		SELECT
			c_custkey
		FROM
			CUSTOMER

		EXCEPT -- o que eu vou subtrair da seleção feita acima

            SELECT
                c_custkey
            FROM
                CUSTOMER
            INNER JOIN
                ORDERS ON o_custkey=c_custkey
            WHERE
                o_comment like "%special request%"
    );