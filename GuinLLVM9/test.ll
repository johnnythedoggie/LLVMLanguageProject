; ModuleID = 'moduleName'
source_filename = "moduleName"

@scanf_format = private unnamed_addr constant [3 x i8] c"%u\00", align 1
@printf_format = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1

define void @main() {
entry:
%y = alloca i32, align 4
store i32 0, i32* %y, align 4
%0 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @scanf_format, i32 0, i32 0), i32* %y)
%z = load i32, i32* %y, align 4
%1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 4)
%2 = load i32, i32* %y, align 4
%3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %2)
%4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %z)
ret void
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
