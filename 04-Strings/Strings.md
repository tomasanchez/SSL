# Strings

## Funciones

#### getLength()

```hs
getLength :: Sigma* -> N

let getLength(a) a in Sigma*/ {a = {a_0, a_1, ..., a_n} : n in N : getLength(a) = n-1 if n>0, getLength(a+) = 0  if n = 0 }
```

### isEmpty()

```hs
isEmpty :: Sigma* -> Boolean

let isEmpty(a), a in Sigma* / {a = {a_0, a_1, ..., a_n} : n in N : getLength(a) = True if n = 0 }
```

### Power()

```hs
Power :: Sigma* X N -> Sigma*

let Power(a, m) / {a = {a_0, a_1, ..., a_n} : n in N : Power (a) = b, b in  Sigma* : b = append(a, a) and |b| = (|a|) (m)} }
```

### append()

```hs
append :: Sigma* X Sigma* -> Sigma*

let append(a, b) a, b in Sigma* / {a = {a_0, a_1, ..., a_n}, b = {b_0, _1, ..., b_n} : n, m in N : append(a, b) = c, c in Sigma* : c = {a_0, a_1, ..., a_n, b_0, ..., b_m,}}
```
