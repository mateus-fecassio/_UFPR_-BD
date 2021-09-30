SELECT 
    distinct(n_name), sum(l_quantity) AS number_of_itens
FROM
	NATION
INNER JOIN
	CUSTOMER ON n_nationkey=c_nationkey
INNER JOIN
	ORDERS ON o_custkey=c_custkey
INNER JOIN
	LINEITEM ON l_orderkey=o_orderkey
GROUP BY
	n_name
ORDER BY
	number_of_itens desc limit 10;