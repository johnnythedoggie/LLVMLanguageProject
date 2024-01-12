; ModuleID = 'moduleName'
source_filename = "moduleName"

@scanf_format = private unnamed_addr constant [3 x i8] c"%u\00", align 1

define void @main() {
	entry:
	%y = alloca i32 ({})*, align 8
	store i32 ({})* @input, i32 ({})** %y, align 8
	%0 = load i32 ({})*, i32 ({})** %y, align 8
	%1 = call i32 %0({} zeroinitializer)
	ret void
}

declare i32 @scanf(i8*, ...)

define i32 @input({} %0) {
	entry:
	%1 = alloca i32, align 4
	%2 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @scanf_format, i32 0, i32 0), i32* %1)
	%3 = load i32, i32* %1, align 4
	ret i32 %3
}
