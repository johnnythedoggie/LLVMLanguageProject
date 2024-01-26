; ModuleID = 'moduleName'
source_filename = "moduleName"

@printf_format = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1
@scanf_format = private unnamed_addr constant [3 x i8] c"%u\00", align 1

define void @main() {
entry:
%while = alloca { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)*, {}** }, align 8
%0 = alloca [0 x {}*], align 8
%1 = getelementptr [0 x {}*], [0 x {}*]* %0, i32 0, i32 0
%2 = insertvalue { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)*, {}** } { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)* @function11, {}** null }, {}** %1, 1
store { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)*, {}** } %2, { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)*, {}** }* %while, align 8
%3 = bitcast { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)*, {}** }* %while to {}*
%4 = alloca [1 x {}*], align 8
%5 = getelementptr [1 x {}*], [1 x {}*]* %4, i32 0, i32 0
store {}* %3, {}** %5, align 8
%6 = getelementptr [1 x {}*], [1 x {}*]* %4, i32 0, i32 0
%7 = insertvalue { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)*, {}** } { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)* @function12, {}** null }, {}** %6, 1
store { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)*, {}** } %7, { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)*, {}** }* %while, align 8
%cw = alloca { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** }, align 8
%8 = alloca [0 x {}*], align 8
%9 = getelementptr [0 x {}*], [0 x {}*]* %8, i32 0, i32 0
%10 = insertvalue { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** } { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)* @function14, {}** null }, {}** %9, 1
store { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** } %10, { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** }* %cw, align 8
%11 = bitcast { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** }* %cw to {}*
%12 = alloca [1 x {}*], align 8
%13 = getelementptr [1 x {}*], [1 x {}*]* %12, i32 0, i32 0
store {}* %11, {}** %13, align 8
%14 = getelementptr [1 x {}*], [1 x {}*]* %12, i32 0, i32 0
%15 = insertvalue { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** } { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)* @function16, {}** null }, {}** %14, 1
store { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** } %15, { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** }* %cw, align 8
%x = alloca i32, align 4
store i32 4, i32* %x, align 4
%16 = bitcast i32* %x to {}*
%17 = alloca [1 x {}*], align 8
%18 = getelementptr [1 x {}*], [1 x {}*]* %17, i32 0, i32 0
store {}* %16, {}** %18, align 8
%19 = getelementptr [1 x {}*], [1 x {}*]* %17, i32 0, i32 0
%condition = insertvalue { i1 ({}, {}**)*, {}** } { i1 ({}, {}**)* @function19, {}** null }, {}** %19, 1
%cw1 = load { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** }, { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** }* %cw, align 8
%20 = extractvalue { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** } %cw1, 0
%21 = extractvalue { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** } %cw1, 1
%22 = call { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } %20({ i1 ({}, {}**)*, {}** } %condition, {}** %21)
%23 = extractvalue { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } %22, 0
%24 = extractvalue { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } %22, 1
%25 = bitcast i32* %x to {}*
%26 = alloca [1 x {}*], align 8
%27 = getelementptr [1 x {}*], [1 x {}*]* %26, i32 0, i32 0
store {}* %25, {}** %27, align 8
%28 = getelementptr [1 x {}*], [1 x {}*]* %26, i32 0, i32 0
%29 = insertvalue { {} ({}, {}**)*, {}** } { {} ({}, {}**)* @function20, {}** null }, {}** %28, 1
%30 = call {} %23({ {} ({}, {}**)*, {}** } %29, {}** %24)
%31 = call {} @output(i32 3)
ret void
}

define {} @function11({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } } %0, {}** %1) {
entry:
ret {} zeroinitializer
}

define {} @function12({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } } %arg, {}** %0) {
entry:
%1 = extractvalue { { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } } %arg, 0
%2 = extractvalue { i1 ({}, {}**)*, {}** } %1, 0
%3 = extractvalue { i1 ({}, {}**)*, {}** } %1, 1
%4 = call i1 %2({} zeroinitializer, {}** %3)
%5 = call {} ({ {} ({}, {}**)*, {}** })* @if(i1 %4)
%6 = getelementptr {}*, {}** %0, i32 0
%7 = load {}*, {}** %6, align 8
%8 = bitcast {}* %7 to { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)*, {}** }*
%9 = alloca { { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, align 8
store { { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } } %arg, { { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }* %9, align 8
%10 = bitcast { { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }* %9 to {}*
%11 = bitcast { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)*, {}** }* %8 to {}*
%12 = alloca [2 x {}*], align 8
%13 = getelementptr [2 x {}*], [2 x {}*]* %12, i32 0, i32 0
store {}* %10, {}** %13, align 8
%14 = getelementptr [2 x {}*], [2 x {}*]* %12, i32 0, i32 1
store {}* %11, {}** %14, align 8
%15 = getelementptr [2 x {}*], [2 x {}*]* %12, i32 0, i32 0
%16 = insertvalue { {} ({}, {}**)*, {}** } { {} ({}, {}**)* @function13, {}** null }, {}** %15, 1
%17 = call {} %5({ {} ({}, {}**)*, {}** } %16)
ret {} zeroinitializer
}

define {} ({ {} ({}, {}**)*, {}** })* @if(i1 %0) {
entry:
%1 = select i1 %0, {} ({ {} ({}, {}**)*, {}** })* @call, {} ({ {} ({}, {}**)*, {}** })* @ignore
ret {} ({ {} ({}, {}**)*, {}** })* %1
}

define {} @call({ {} ({}, {}**)*, {}** } %0) {
entry:
%1 = extractvalue { {} ({}, {}**)*, {}** } %0, 0
%2 = extractvalue { {} ({}, {}**)*, {}** } %0, 1
%3 = call {} %1({} zeroinitializer, {}** %2)
ret {} zeroinitializer
}

define {} @ignore({ {} ({}, {}**)*, {}** } %0) {
entry:
ret {} zeroinitializer
}

define {} @function13({} %0, {}** %1) {
entry:
%2 = getelementptr {}*, {}** %1, i32 0
%3 = load {}*, {}** %2, align 8
%4 = bitcast {}* %3 to { { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }*
%arg = load { { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, { { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }* %4, align 8
%5 = extractvalue { { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } } %arg, 1
%6 = extractvalue { {} ({}, {}**)*, {}** } %5, 0
%7 = extractvalue { {} ({}, {}**)*, {}** } %5, 1
%8 = call {} %6({} zeroinitializer, {}** %7)
%9 = getelementptr {}*, {}** %1, i32 1
%10 = load {}*, {}** %9, align 8
%11 = bitcast {}* %10 to { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)*, {}** }*
%while = load { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)*, {}** }, { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)*, {}** }* %11, align 8
%12 = extractvalue { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)*, {}** } %while, 0
%13 = extractvalue { {} ({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } }, {}**)*, {}** } %while, 1
%14 = call {} %12({ { i1 ({}, {}**)*, {}** }, { {} ({}, {}**)*, {}** } } %arg, {}** %13)
ret {} zeroinitializer
}

define { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } @function14({ i1 ({}, {}**)*, {}** } %0, {}** %1) {
entry:
%2 = alloca [0 x {}*], align 8
%3 = getelementptr [0 x {}*], [0 x {}*]* %2, i32 0, i32 0
%4 = insertvalue { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } { {} ({ {} ({}, {}**)*, {}** }, {}**)* @function15, {}** null }, {}** %3, 1
ret { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } %4
}

define {} @function15({ {} ({}, {}**)*, {}** } %0, {}** %1) {
entry:
ret {} zeroinitializer
}

define { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } @function16({ i1 ({}, {}**)*, {}** } %condition, {}** %0) {
entry:
%1 = getelementptr {}*, {}** %0, i32 0
%2 = load {}*, {}** %1, align 8
%3 = bitcast {}* %2 to { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** }*
%4 = bitcast { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** }* %3 to {}*
%5 = alloca { i1 ({}, {}**)*, {}** }, align 8
store { i1 ({}, {}**)*, {}** } %condition, { i1 ({}, {}**)*, {}** }* %5, align 8
%6 = bitcast { i1 ({}, {}**)*, {}** }* %5 to {}*
%7 = alloca [2 x {}*], align 8
%8 = getelementptr [2 x {}*], [2 x {}*]* %7, i32 0, i32 0
store {}* %4, {}** %8, align 8
%9 = getelementptr [2 x {}*], [2 x {}*]* %7, i32 0, i32 1
store {}* %6, {}** %9, align 8
%10 = getelementptr [2 x {}*], [2 x {}*]* %7, i32 0, i32 0
%recurse = insertvalue { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } { {} ({ {} ({}, {}**)*, {}** }, {}**)* @function17, {}** null }, {}** %10, 1
%11 = alloca [0 x {}*], align 8
%12 = getelementptr [0 x {}*], [0 x {}*]* %11, i32 0, i32 0
%ignore = insertvalue { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } { {} ({ {} ({}, {}**)*, {}** }, {}**)* @function18, {}** null }, {}** %12, 1
%13 = extractvalue { i1 ({}, {}**)*, {}** } %condition, 0
%14 = extractvalue { i1 ({}, {}**)*, {}** } %condition, 1
%15 = call i1 %13({} zeroinitializer, {}** %14)
%16 = select i1 %15, { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } %recurse, { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } %ignore
ret { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } %16
}

define {} @function17({ {} ({}, {}**)*, {}** } %action, {}** %0) {
entry:
%1 = extractvalue { {} ({}, {}**)*, {}** } %action, 0
%2 = extractvalue { {} ({}, {}**)*, {}** } %action, 1
%3 = call {} %1({} zeroinitializer, {}** %2)
%4 = getelementptr {}*, {}** %0, i32 0
%5 = load {}*, {}** %4, align 8
%6 = bitcast {}* %5 to { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** }*
%7 = getelementptr {}*, {}** %0, i32 1
%8 = load {}*, {}** %7, align 8
%9 = bitcast {}* %8 to { i1 ({}, {}**)*, {}** }*
%condition = load { i1 ({}, {}**)*, {}** }, { i1 ({}, {}**)*, {}** }* %9, align 8
%cw = load { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** }, { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** }* %6, align 8
%10 = extractvalue { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** } %cw, 0
%11 = extractvalue { { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } ({ i1 ({}, {}**)*, {}** }, {}**)*, {}** } %cw, 1
%12 = call { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } %10({ i1 ({}, {}**)*, {}** } %condition, {}** %11)
%13 = extractvalue { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } %12, 0
%14 = extractvalue { {} ({ {} ({}, {}**)*, {}** }, {}**)*, {}** } %12, 1
%15 = call {} %13({ {} ({}, {}**)*, {}** } %action, {}** %14)
ret {} zeroinitializer
}

define {} @function18({ {} ({}, {}**)*, {}** } %0, {}** %1) {
entry:
ret {} zeroinitializer
}

define i1 @function19({} %0, {}** %1) {
entry:
%2 = call {} @output(i32 1)
%3 = getelementptr {}*, {}** %1, i32 0
%4 = load {}*, {}** %3, align 8
%5 = bitcast {}* %4 to i32*
%x = load i32, i32* %5, align 4
%6 = insertvalue { i32, i32 } zeroinitializer, i32 %x, 0
%7 = insertvalue { i32, i32 } %6, i32 5, 1
%8 = call i1 @equals({ i32, i32 } %7)
%9 = insertvalue { i1, i1 } zeroinitializer, i1 %8, 0
%x1 = load i32, i32* %5, align 4
%10 = insertvalue { i32, i32 } zeroinitializer, i32 %x1, 0
%11 = insertvalue { i32, i32 } %10, i32 4, 1
%12 = call i1 @equals({ i32, i32 } %11)
%13 = insertvalue { i1, i1 } %9, i1 %12, 1
%14 = call i1 @or({ i1, i1 } %13)
ret i1 %14
}

define {} @output(i32 %0) {
entry:
%1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %0)
ret {} zeroinitializer
}

declare i32 @printf(i8*, ...)

define i1 @or({ i1, i1 } %0) {
entry:
%1 = extractvalue { i1, i1 } %0, 0
%2 = call i1 @not(i1 %1)
%3 = insertvalue { i1, i1 } zeroinitializer, i1 %2, 0
%4 = extractvalue { i1, i1 } %0, 1
%5 = call i1 @not(i1 %4)
%6 = insertvalue { i1, i1 } %3, i1 %5, 1
%7 = call i1 @and({ i1, i1 } %6)
%8 = call i1 @not(i1 %7)
ret i1 %8
}

define i1 @not(i1 %0) {
entry:
%1 = xor i1 %0, true
ret i1 %1
}

define i1 @and({ i1, i1 } %0) {
entry:
%1 = extractvalue { i1, i1 } %0, 0
%2 = extractvalue { i1, i1 } %0, 1
%3 = and i1 %1, %2
ret i1 %3
}

define i1 @equals({ i32, i32 } %0) {
entry:
%1 = extractvalue { i32, i32 } %0, 0
%2 = extractvalue { i32, i32 } %0, 1
%3 = icmp eq i32 %1, %2
ret i1 %3
}

define {} @function20({} %0, {}** %1) {
entry:
%2 = call {} @output(i32 2)
%3 = getelementptr {}*, {}** %1, i32 0
%4 = load {}*, {}** %3, align 8
%5 = bitcast {}* %4 to i32*
%6 = call i32 @input({} zeroinitializer)
store i32 %6, i32* %5, align 4
ret {} zeroinitializer
}

define i32 @input({} %0) {
entry:
%1 = alloca i32, align 4
%2 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @scanf_format, i32 0, i32 0), i32* %1)
%3 = load i32, i32* %1, align 4
ret i32 %3
}

declare i32 @scanf(i8*, ...)
