# My Solitaire rewrite

### flow chart

<!-- gfmd-start -->
```mermaid
graph TD
A[Game Mod] -->B{Game Table}
B -->C(Card 0)
B -->D(Card 1)
B -->E(Card 2)
B -->F(Card N)
graph LR
E === F
subgraph left 42 Puck Cards
C
D
E
F
end
```
<!-- gfmd-end -->
