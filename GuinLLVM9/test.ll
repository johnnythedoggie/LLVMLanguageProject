; ModuleID = 'moduleName'
source_filename = "moduleName"

@printf_format = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1
@scanf_format = private unnamed_addr constant [3 x i8] c"%u\00", align 1

define void @main() {
	entry:
	%x = alloca {} ({})*, align 8
	store {} ({})* @function2, {} ({})** %x, align 8
	store {} ({})* @function3, {} ({})** %x, align 8
	%y = alloca i32, align 4
	%0 = call i32 @input({} zeroinitializer)
	store i32 %0, i32* %y, align 4
	%1 = load {} ({})*, {} ({})** %x, align 8
	%2 = call {} %1({} zeroinitializer)
	%3 = load i32, i32* %y, align 4
	%4 = call {} @output(i32 %3)
	ret void
}

define {} @function2({} %0) {
	entry:
	%1 = call {} @output(i32 5)
	%2 = call {} @output(i32 4)
	%3 = call {} @output(i32 3)
	%4 = call {} @output(i32 2)
	ret {} zeroinitializer
}

declare i32 @printf(i8*, ...)

define {} @output(i32 %0) {
	entry:
	%1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %0)
	ret {} zeroinitializer
}

define {} @function3({} %0) {
	entry:
	ret {} zeroinitializer
}

declare i32 @scanf(i8*, ...)

define i32 @input({} %0) {
entry:
%1 = alloca i32, align 4
%2 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @scanf_format, i32 0, i32 0), i32* %1)
%3 = load i32, i32* %1, align 4
ret i32 %3
}
