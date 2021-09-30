SELECT 
    distinct(n_name), count(c_custkey) AS number_of_orders
FROM
	NATION
INNER JOIN
	CUSTOMER ON  n_nationkey=c_nationkey
INNER JOIN
	ORDERS ON o_custkey=c_custkey
GROUP BY
	n_name
ORDER BY
	number_of_orders desc;