; ModuleID = 'moduleName'
source_filename = "moduleName"

@printf_format = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1

define void @main() {
entry:
%0 = call {} @x(i32 5)
ret void
}

define {} @x(i32 %0) {
entry:
%1 = call {} @output(i32 %0)
%2 = call {} @output(i32 %0)
%3 = call {} @output(i32 %0)
ret {} zeroinitializer
}

declare i32 @printf(i8*, ...)

define {} @output(i32 %0) {
entry:
%1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %0)
ret {} zeroinitializer
}
