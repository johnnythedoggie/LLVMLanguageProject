# My LLVM Language Project

I've tentatively decided on the name Guin for the language.

If you're reviewing my code, glance at this and then go check out Parser or PStatement or CValue!
It's a one person project with a lot of changes so documentation isn't great, but the code should be readable!

## Language Features

The idea is to let things that aren't first class in other languages be first class here.
Functions, types, etc are just normal values that are treated like any other. 

### First Class Everything

#### Functions

One of the primary goals of Guin was to impelement first class functions.
A function can be `pure` or `impure`. 
Pure functions cannot capture surrounding variables, while impure functions can.
You can use the correspinding keyword or let the compiler decide for you.

```
const exampleFunc1 = pure Void -> Int {
    return 5
}

var x = userInput()
const exampleFunc2 = impure Void -> Int {
    return x
}


```
#### Types

Types are also first class entities in Guin:

```
const Point = (x: Int, y: Int)

const example = (point: Point, type: Type) -> Int { ... }

example((5, 5), Int)
example((x = 1, y = 2), Bool)
example((2, 8), (singleElement: Point))
```

#### Return (In Developement)

`return` is first class as well.
Like `if`, instead of being a satement, `return` is a function.
It's type is `impure ReturnType -> Never`, where `Never` is an uninhabited type.
Any function that returns `Never` is garenteed to exit the current scope.

### Tuples

Tuples are ordered, labeled collections of zero or more values.
They are written like so:

```
(a = 1, b = Bool, c = (x = 2, y = 3))
(label1 = value1, label2 = value2)
()
```
Functions only take one argument, but the argument is often a tuple.
You can also return a tuple from a function to get multiple return types.

You write the type of a tuple similarly, but use `: type` instead of ` = value`.
In the case of the empty tuple, these names would collide so `Void` is used as the type name.



### Control Flow

In Guin, `if` is not a keyword, it's a function. 
The type of `if` is `Bool -> ((Void -> Void) -> Void)`, meaning you call it with a condition first, then call the result of that with an action to perform.
The language can figure out the call order as well as infer the type of the function, so it ends up looking very normal:

```
if condition {
  action
}

```

Similarly, `while` and other control flow can be implemented as functions.

## How to run

Feel free to download it and then build and run it from the command line, passing in a Guin source file.  This will be tokenized, parsed, and compiled into LLVM IR, which will be output to the console.

`guin input.txt` <- this will print out the IR

You can run the IR any way you want, but the eaisest way (on a Mac at least) is to pipe the output into clang and then run the `./a.out`.

## Other


This is a personal project that is in progress and not maintained for public use. That being said, if anyone stumbles across this, feel free to take any and all you want from it.

