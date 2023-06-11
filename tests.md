# Test cases:

### Recovery:
Search: "apartamento casa ninguem porem quem quer tambem"
Expected result: d1.txt

Search: "casa em entrar ninguem todos quem quer sairam"
Expected result: d2.txt

Search: "apartamento esta ninguem todos no quem sairam"
Expected result: d3.txt

Search: "quem"
Expected result: d2.txt, d1.txt, d3.txt

Search: "ninguem"
Expected result: d1.txt, d2.txt, d3.txt

Search: "todos"
Expected result: d2.txt, d3.txt