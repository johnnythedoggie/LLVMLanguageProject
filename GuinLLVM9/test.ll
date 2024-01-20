

; ModuleID = 'moduleName'
source_filename = "moduleName"

@scanf_format = private unnamed_addr constant [3 x i8] c"%u\00", align 1
@printf_format = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1

define void @main() {
	entry:
	%x = alloca i32, align 4
	store i32 0, i32* %x, align 4
	%0 = call {} ({ {} ({}, {}**)*, {}** })* @if(i1 true)
	%1 = bitcast i32* %x to {}*
	%2 = alloca [1 x {}*], align 8
	%3 = getelementptr [1 x {}*], [1 x {}*]* %2, i32 0, i32 0
	store {}* %1, {}** %3, align 8
	%4 = getelementptr [1 x {}*], [1 x {}*]* %2, i32 0, i32 0
	%5 = insertvalue { {} ({}, {}**)*, {}** } { {} ({}, {}**)* @ifBody, {}** null }, {}** %4, 1
	%6 = call {} %0({ {} ({}, {}**)*, {}** } %5)
	%7 = load i32, i32* %x, align 4
	%8 = call {} @output(i32 %7)
	ret void
}

define {} ({ {} ({}, {}**)*, {}** })* @if(i1 %0) {
	entry:
	ret {} ({ {} ({}, {}**)*, {}** })* @call
}

define {} @call({ {} ({}, {}**)*, {}** } %0) {
	entry:
	%1 = extractvalue { {} ({}, {}**)*, {}** } %0, 0
	%2 = extractvalue { {} ({}, {}**)*, {}** } %0, 1
	%3 = call {} %1({} zeroinitializer, {}** %2)
	ret {} zeroinitializer
}

define {} @ifBody({} %0, {}** %1) {
	entry:
	%2 = getelementptr {}*, {}** %1, i32 0
	%3 = load {}*, {}** %2, align 8
	%4 = bitcast {}* %3 to i32*
	%5 = call i32 @input({} zeroinitializer)
	store i32 %5, i32* %4, align 4
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

define {} @output(i32 %0) {
	entry:
	%1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %0)
	ret {} zeroinitializer
}

declare i32 @printf(i8*, ...)
Program ended with exit code: 0
