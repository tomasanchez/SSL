# Parte II - Strings

## Funciones

### getLength

```s
Name:           getLength
Description:    obtains number of characters in a word
Return Value:   number of characters  
```

![getLength(x)](data/getLength.png)

```c
Example:
getLength("Hello")  = 5
getLength("World!") = 6
getLength("")       = 0
```

### isEmpty

```s
Name:           isEmpty
Description:    verifies if the string has any character
Return Value:   True if is empty, otherwise False  
```

![isEmpty](data/isEmpty.png)

```c
Example:
isEmpty("Hello")    = False
isEmpty("")         = True
isEmpty(" ")        = False
```

### isEqual


```s
Name:           isEqual
Description:    compares if two strings have exactly the same characters
Return Value:   True if has the same characters, otherwise false
```

![isEqual](data/isEqual.png)

```c
Example:
isEqual("Hello", "hello") = False
isEqual("World!", "World!") = True
```

### Power

```s
Name:           Power
Description:    Applies append N times with itself or nules the string if zero
Return Value:   String appended n times, or empty string
```

![power](data/power.png)

```c
Example:
power("Hello", 2) = "HelloHello"
power("World", 0) = ""
power("foo", -10) = ""
```

### append

```s
Name:           append
Description:    concatenates the second string into the first one
Return Value:   Void
```

![append](data/append.png)

```c
Example:
append("Hello", " World!") = "Hello World!"
append ("", "Hello") = "Hello"
```
