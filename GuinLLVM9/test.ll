; ModuleID = 'moduleName'
source_filename = "moduleName"

@scanf_format = private unnamed_addr constant [3 x i8] c"%u\00", align 1
@printf_format = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1

define void @main() {
entry:
%0 = alloca i32, align 4
%1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @scanf_format, i32 0, i32 0), i32* %0)
%x = load i32, i32* %0, align 4
%2 = alloca i32, align 4
%3 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @scanf_format, i32 0, i32 0), i32* %2)
%4 = load i32, i32* %2, align 4
%5 = alloca i32, align 4
%6 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @scanf_format, i32 0, i32 0), i32* %5)
%y = load i32, i32* %5, align 4
%7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 5)
%8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %x)
%9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %y)
ret void
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
