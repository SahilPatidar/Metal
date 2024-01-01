define void @RedBlackTree_deletion(i32 %RedBlackTree_data) {
entry:
  %RedBlackTree_data1 = alloca i32, align 4
  store i32 %RedBlackTree_data, ptr %RedBlackTree_data1, align 4
  %0 = alloca [98 x ptr], align 8
  %1 = alloca ptr, align 8
  %2 = alloca ptr, align 8
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca [98 x i32], align 4
  %8 = alloca i32, align 4
  store i32 0, ptr %8, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = load ptr, ptr @RedBlackTree_root, align 8
  %13 = icmp eq ptr %12, null
  br i1 %13, label %if, label %end

if:                                               ; preds = %entry
  %14 = call i32 (ptr, ...) @printf(ptr @26)
  ret void

end:                                              ; preds = %entry
  %15 = load ptr, ptr @RedBlackTree_root, align 8
  store ptr %15, ptr %1, align 8
  br label %cond

cond:                                             ; preds = %end5, %end
  %16 = load ptr, ptr %1, align 8
  %17 = icmp ne ptr %16, null
  br i1 %17, label %loop, label %end6

loop:                                             ; preds = %cond
  %18 = load ptr, ptr %1, align 8
  %19 = getelementptr inbounds %RedBlackTree_rbNode, ptr %18, i32 0, i32 0
  %20 = load i32, ptr %RedBlackTree_data1, align 4
  %21 = load i32, ptr %19, align 4
  %22 = sub nsw i32 %20, %21
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %if2, label %end3

if2:                                              ; preds = %loop
  br label %end6

end3:                                             ; preds = %loop
  %24 = load ptr, ptr %1, align 8
  %25 = getelementptr inbounds %RedBlackTree_rbNode, ptr %24, i32 0, i32 0
  %26 = load i32, ptr %RedBlackTree_data1, align 4
  %27 = load i32, ptr %25, align 4
  %28 = sub nsw i32 %26, %27
  %29 = icmp sgt i32 %28, 0
  br i1 %29, label %if4, label %else

if4:                                              ; preds = %end3
  store i32 1, ptr %9, align 4
  br label %end5

else:                                             ; preds = %end3
  store i32 0, ptr %9, align 4
  br label %end5

end5:                                             ; preds = %else, %if4
  %30 = load i32, ptr %8, align 4
  %31 = sext i32 %30 to i64
  %32 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %31
  %33 = load ptr, ptr %1, align 8
  store ptr %33, ptr %32, align 8
  %34 = load i32, ptr %8, align 4
  %35 = sext i32 %34 to i64
  %36 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %35
  %37 = load i32, ptr %9, align 4
  store i32 %37, ptr %36, align 4
  %38 = load i32, ptr %8, align 4
  %39 = add i32 %38, 1
  store i32 %39, ptr %8, align 4
  %40 = load ptr, ptr %1, align 8
  %41 = getelementptr inbounds %RedBlackTree_rbNode, ptr %40, i32 0, i32 2
  %42 = load i32, ptr %9, align 4
  %43 = sext i32 %42 to i64
  %44 = getelementptr inbounds [2 x ptr], ptr %41, i64 0, i64 %43
  %45 = load ptr, ptr %44, align 8
  store ptr %45, ptr %1, align 8
  br label %cond

end6:                                             ; preds = %if2, %cond
  %46 = load ptr, ptr %1, align 8
  %47 = getelementptr inbounds %RedBlackTree_rbNode, ptr %46, i32 0, i32 2
  %48 = getelementptr inbounds [2 x ptr], ptr %47, i64 0, i64 1
  %49 = load ptr, ptr %48, align 8
  %50 = icmp eq ptr %49, null
  br i1 %50, label %if7, label %else14

if7:                                              ; preds = %end6
  %51 = load ptr, ptr %1, align 8
  %52 = load ptr, ptr @RedBlackTree_root, align 8
  %53 = icmp eq ptr %51, %52
  %54 = load ptr, ptr %1, align 8
  %55 = getelementptr inbounds %RedBlackTree_rbNode, ptr %54, i32 0, i32 2
  %56 = getelementptr inbounds [2 x ptr], ptr %55, i64 0, i64 0
  %57 = load ptr, ptr %56, align 8
  %58 = icmp eq ptr %57, null
  %59 = select i1 %53, i1 %58, i1 false
  br i1 %59, label %if8, label %else9

if8:                                              ; preds = %if7
  %60 = load ptr, ptr %1, align 8
  call void @free(ptr %60)
  store ptr null, ptr @RedBlackTree_root, align 8
  br label %end13

else9:                                            ; preds = %if7
  %61 = load ptr, ptr %1, align 8
  %62 = load ptr, ptr @RedBlackTree_root, align 8
  %63 = icmp eq ptr %61, %62
  br i1 %63, label %if10, label %else11

if10:                                             ; preds = %else9
  %64 = load ptr, ptr %1, align 8
  %65 = getelementptr inbounds %RedBlackTree_rbNode, ptr %64, i32 0, i32 2
  %66 = getelementptr inbounds [2 x ptr], ptr %65, i64 0, i64 0
  %67 = load ptr, ptr %66, align 8
  store ptr %67, ptr @RedBlackTree_root, align 8
  %68 = load ptr, ptr %1, align 8
  call void @free(ptr %68)
  br label %end12

else11:                                           ; preds = %else9
  %69 = load i32, ptr %8, align 4
  %70 = sub nsw i32 %69, 1
  %71 = sext i32 %70 to i64
  %72 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %71
  %73 = load ptr, ptr %72, align 8
  %74 = getelementptr inbounds %RedBlackTree_rbNode, ptr %73, i32 0, i32 2
  %75 = load i32, ptr %8, align 4
  %76 = sub nsw i32 %75, 1
  %77 = sext i32 %76 to i64
  %78 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %77
  %79 = load i32, ptr %78, align 4
  %80 = sext i32 %79 to i64
  %81 = getelementptr inbounds [2 x ptr], ptr %74, i64 0, i64 %80
  %82 = load ptr, ptr %1, align 8
  %83 = getelementptr inbounds %RedBlackTree_rbNode, ptr %82, i32 0, i32 2
  %84 = getelementptr inbounds [2 x ptr], ptr %83, i64 0, i64 0
  %85 = load ptr, ptr %84, align 8
  store ptr %85, ptr %81, align 8
  br label %end12

end12:                                            ; preds = %else11, %if10
  br label %end13

end13:                                            ; preds = %end12, %if8
  br label %end30

else14:                                           ; preds = %end6
  %86 = load ptr, ptr %1, align 8
  %87 = getelementptr inbounds %RedBlackTree_rbNode, ptr %86, i32 0, i32 2
  %88 = getelementptr inbounds [2 x ptr], ptr %87, i64 0, i64 1
  %89 = load ptr, ptr %88, align 8
  store ptr %89, ptr %2, align 8
  %90 = load ptr, ptr %2, align 8
  %91 = getelementptr inbounds %RedBlackTree_rbNode, ptr %90, i32 0, i32 2
  %92 = getelementptr inbounds [2 x ptr], ptr %91, i64 0, i64 0
  %93 = load ptr, ptr %92, align 8
  %94 = icmp eq ptr %93, null
  br i1 %94, label %if15, label %else19

if15:                                             ; preds = %else14
  %95 = load ptr, ptr %2, align 8
  %96 = getelementptr inbounds %RedBlackTree_rbNode, ptr %95, i32 0, i32 2
  %97 = getelementptr inbounds [2 x ptr], ptr %96, i64 0, i64 0
  %98 = load ptr, ptr %1, align 8
  %99 = getelementptr inbounds %RedBlackTree_rbNode, ptr %98, i32 0, i32 2
  %100 = getelementptr inbounds [2 x ptr], ptr %99, i64 0, i64 0
  %101 = load ptr, ptr %100, align 8
  store ptr %101, ptr %97, align 8
  %102 = load ptr, ptr %2, align 8
  %103 = getelementptr inbounds %RedBlackTree_rbNode, ptr %102, i32 0, i32 1
  %104 = load i32, ptr %103, align 4
  store i32 %104, ptr %11, align 4
  %105 = load ptr, ptr %2, align 8
  %106 = getelementptr inbounds %RedBlackTree_rbNode, ptr %105, i32 0, i32 1
  %107 = load ptr, ptr %1, align 8
  %108 = getelementptr inbounds %RedBlackTree_rbNode, ptr %107, i32 0, i32 1
  %109 = load i32, ptr %108, align 4
  store i32 %109, ptr %106, align 4
  %110 = load ptr, ptr %1, align 8
  %111 = getelementptr inbounds %RedBlackTree_rbNode, ptr %110, i32 0, i32 1
  %112 = load i32, ptr %11, align 4
  store i32 %112, ptr %111, align 4
  %113 = load ptr, ptr %1, align 8
  %114 = load ptr, ptr @RedBlackTree_root, align 8
  %115 = icmp eq ptr %113, %114
  br i1 %115, label %if16, label %else17

if16:                                             ; preds = %if15
  %116 = load ptr, ptr %2, align 8
  store ptr %116, ptr @RedBlackTree_root, align 8
  br label %end18

else17:                                           ; preds = %if15
  %117 = load i32, ptr %8, align 4
  %118 = sub nsw i32 %117, 1
  %119 = sext i32 %118 to i64
  %120 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %119
  %121 = load ptr, ptr %120, align 8
  %122 = getelementptr inbounds %RedBlackTree_rbNode, ptr %121, i32 0, i32 2
  %123 = load i32, ptr %8, align 4
  %124 = sub nsw i32 %123, 1
  %125 = sext i32 %124 to i64
  %126 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %125
  %127 = load i32, ptr %126, align 4
  %128 = sext i32 %127 to i64
  %129 = getelementptr inbounds [2 x ptr], ptr %122, i64 0, i64 %128
  %130 = load ptr, ptr %2, align 8
  store ptr %130, ptr %129, align 8
  br label %end18

end18:                                            ; preds = %else17, %if16
  %131 = load i32, ptr %8, align 4
  %132 = sext i32 %131 to i64
  %133 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %132
  store i32 1, ptr %133, align 4
  %134 = load i32, ptr %8, align 4
  %135 = sext i32 %134 to i64
  %136 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %135
  %137 = load ptr, ptr %2, align 8
  store ptr %137, ptr %136, align 8
  %138 = load i32, ptr %8, align 4
  %139 = add i32 %138, 1
  store i32 %139, ptr %8, align 4
  br label %end29

else19:                                           ; preds = %else14
  %140 = load i32, ptr %8, align 4
  store i32 %140, ptr %10, align 4
  %141 = load i32, ptr %8, align 4
  %142 = add i32 %141, 1
  store i32 %142, ptr %8, align 4
  br label %cond20

cond20:                                           ; preds = %end23, %else19
  br i1 true, label %loop21, label %end24

loop21:                                           ; preds = %cond20
  %143 = load i32, ptr %8, align 4
  %144 = sext i32 %143 to i64
  %145 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %144
  store i32 0, ptr %145, align 4
  %146 = load i32, ptr %8, align 4
  %147 = sext i32 %146 to i64
  %148 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %147
  %149 = load ptr, ptr %2, align 8
  store ptr %149, ptr %148, align 8
  %150 = load i32, ptr %8, align 4
  %151 = add i32 %150, 1
  store i32 %151, ptr %8, align 4
  %152 = load ptr, ptr %2, align 8
  %153 = getelementptr inbounds %RedBlackTree_rbNode, ptr %152, i32 0, i32 2
  %154 = getelementptr inbounds [2 x ptr], ptr %153, i64 0, i64 0
  %155 = load ptr, ptr %154, align 8
  store ptr %155, ptr %3, align 8
  %156 = load ptr, ptr %3, align 8
  %157 = getelementptr inbounds %RedBlackTree_rbNode, ptr %156, i32 0, i32 2
  %158 = getelementptr inbounds [2 x ptr], ptr %157, i64 0, i64 0
  %159 = load ptr, ptr %158, align 8
  %160 = icmp eq ptr %159, null
  br i1 %160, label %if22, label %end23

if22:                                             ; preds = %loop21
  br label %end24

end23:                                            ; preds = %loop21
  %161 = load ptr, ptr %3, align 8
  store ptr %161, ptr %2, align 8
  br label %cond20

end24:                                            ; preds = %if22, %cond20
  %162 = load i32, ptr %10, align 4
  %163 = sext i32 %162 to i64
  %164 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %163
  store i32 1, ptr %164, align 4
  %165 = load i32, ptr %10, align 4
  %166 = sext i32 %165 to i64
  %167 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %166
  %168 = load ptr, ptr %3, align 8
  store ptr %168, ptr %167, align 8
  %169 = load i32, ptr %10, align 4
  %170 = icmp sgt i32 %169, 0
  br i1 %170, label %if25, label %end26

if25:                                             ; preds = %end24
  %171 = load i32, ptr %10, align 4
  %172 = sub nsw i32 %171, 1
  %173 = sext i32 %172 to i64
  %174 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %173
  %175 = load ptr, ptr %174, align 8
  %176 = getelementptr inbounds %RedBlackTree_rbNode, ptr %175, i32 0, i32 2
  %177 = load i32, ptr %10, align 4
  %178 = sub nsw i32 %177, 1
  %179 = sext i32 %178 to i64
  %180 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %179
  %181 = load i32, ptr %180, align 4
  %182 = sext i32 %181 to i64
  %183 = getelementptr inbounds [2 x ptr], ptr %176, i64 0, i64 %182
  %184 = load ptr, ptr %3, align 8
  store ptr %184, ptr %183, align 8
  br label %end26

end26:                                            ; preds = %if25, %end24
  %185 = load ptr, ptr %3, align 8
  %186 = getelementptr inbounds %RedBlackTree_rbNode, ptr %185, i32 0, i32 2
  %187 = getelementptr inbounds [2 x ptr], ptr %186, i64 0, i64 0
  %188 = load ptr, ptr %1, align 8
  %189 = getelementptr inbounds %RedBlackTree_rbNode, ptr %188, i32 0, i32 2
  %190 = getelementptr inbounds [2 x ptr], ptr %189, i64 0, i64 0
  %191 = load ptr, ptr %190, align 8
  store ptr %191, ptr %187, align 8
  %192 = load ptr, ptr %2, align 8
  %193 = getelementptr inbounds %RedBlackTree_rbNode, ptr %192, i32 0, i32 2
  %194 = getelementptr inbounds [2 x ptr], ptr %193, i64 0, i64 0
  %195 = load ptr, ptr %3, align 8
  %196 = getelementptr inbounds %RedBlackTree_rbNode, ptr %195, i32 0, i32 2
  %197 = getelementptr inbounds [2 x ptr], ptr %196, i64 0, i64 1
  %198 = load ptr, ptr %197, align 8
  store ptr %198, ptr %194, align 8
  %199 = load ptr, ptr %3, align 8
  %200 = getelementptr inbounds %RedBlackTree_rbNode, ptr %199, i32 0, i32 2
  %201 = getelementptr inbounds [2 x ptr], ptr %200, i64 0, i64 1
  %202 = load ptr, ptr %1, align 8
  %203 = getelementptr inbounds %RedBlackTree_rbNode, ptr %202, i32 0, i32 2
  %204 = getelementptr inbounds [2 x ptr], ptr %203, i64 0, i64 1
  %205 = load ptr, ptr %204, align 8
  store ptr %205, ptr %201, align 8
  %206 = load ptr, ptr %1, align 8
  %207 = load ptr, ptr @RedBlackTree_root, align 8
  %208 = icmp eq ptr %206, %207
  br i1 %208, label %if27, label %end28

if27:                                             ; preds = %end26
  %209 = load ptr, ptr %3, align 8
  store ptr %209, ptr @RedBlackTree_root, align 8
  br label %end28

end28:                                            ; preds = %if27, %end26
  %210 = load ptr, ptr %3, align 8
  %211 = getelementptr inbounds %RedBlackTree_rbNode, ptr %210, i32 0, i32 1
  %212 = load i32, ptr %211, align 4
  store i32 %212, ptr %11, align 4
  %213 = load ptr, ptr %3, align 8
  %214 = getelementptr inbounds %RedBlackTree_rbNode, ptr %213, i32 0, i32 1
  %215 = load ptr, ptr %1, align 8
  %216 = getelementptr inbounds %RedBlackTree_rbNode, ptr %215, i32 0, i32 1
  %217 = load i32, ptr %216, align 4
  store i32 %217, ptr %214, align 4
  %218 = load ptr, ptr %1, align 8
  %219 = getelementptr inbounds %RedBlackTree_rbNode, ptr %218, i32 0, i32 1
  %220 = load i32, ptr %11, align 4
  store i32 %220, ptr %219, align 4
  br label %end29

end29:                                            ; preds = %end28, %end18
  br label %end30

end30:                                            ; preds = %end29, %end13
  %221 = load i32, ptr %8, align 4
  %222 = icmp slt i32 %221, 1
  br i1 %222, label %if31, label %end32

if31:                                             ; preds = %end30
  ret void

end32:                                            ; preds = %end30
  %223 = load ptr, ptr %1, align 8
  %224 = getelementptr inbounds %RedBlackTree_rbNode, ptr %223, i32 0, i32 1
  %225 = load i32, ptr %224, align 4
  %226 = icmp eq i32 %225, 1
  br i1 %226, label %if33, label %end74

if33:                                             ; preds = %end32
  br label %cond34

cond34:                                           ; preds = %end72, %if33
  br i1 true, label %loop35, label %end73

loop35:                                           ; preds = %cond34
  %227 = load i32, ptr %8, align 4
  %228 = sub nsw i32 %227, 1
  %229 = sext i32 %228 to i64
  %230 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %229
  %231 = load ptr, ptr %230, align 8
  %232 = getelementptr inbounds %RedBlackTree_rbNode, ptr %231, i32 0, i32 2
  %233 = load i32, ptr %8, align 4
  %234 = sub nsw i32 %233, 1
  %235 = sext i32 %234 to i64
  %236 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %235
  %237 = load i32, ptr %236, align 4
  %238 = sext i32 %237 to i64
  %239 = getelementptr inbounds [2 x ptr], ptr %232, i64 0, i64 %238
  %240 = load ptr, ptr %239, align 8
  store ptr %240, ptr %4, align 8
  %241 = load ptr, ptr %4, align 8
  %242 = icmp ne ptr %241, null
  %243 = load ptr, ptr %4, align 8
  %244 = getelementptr inbounds %RedBlackTree_rbNode, ptr %243, i32 0, i32 1
  %245 = load i32, ptr %244, align 4
  %246 = icmp eq i32 %245, 0
  %247 = select i1 %242, i1 %246, i1 false
  br i1 %247, label %if36, label %end37

if36:                                             ; preds = %loop35
  %248 = load ptr, ptr %4, align 8
  %249 = getelementptr inbounds %RedBlackTree_rbNode, ptr %248, i32 0, i32 1
  store i32 1, ptr %249, align 4
  br label %end73

end37:                                            ; preds = %loop35
  %250 = load i32, ptr %8, align 4
  %251 = icmp slt i32 %250, 2
  br i1 %251, label %if38, label %end39

if38:                                             ; preds = %end37
  br label %end73

end39:                                            ; preds = %end37
  %252 = load i32, ptr %8, align 4
  %253 = sub nsw i32 %252, 2
  %254 = sext i32 %253 to i64
  %255 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %254
  %256 = load i32, ptr %255, align 4
  %257 = icmp eq i32 %256, 0
  br i1 %257, label %if40, label %else56

if40:                                             ; preds = %end39
  %258 = load i32, ptr %8, align 4
  %259 = sub nsw i32 %258, 1
  %260 = sext i32 %259 to i64
  %261 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %260
  %262 = load ptr, ptr %261, align 8
  %263 = getelementptr inbounds %RedBlackTree_rbNode, ptr %262, i32 0, i32 2
  %264 = getelementptr inbounds [2 x ptr], ptr %263, i64 0, i64 1
  %265 = load ptr, ptr %264, align 8
  store ptr %265, ptr %6, align 8
  %266 = load ptr, ptr %6, align 8
  %267 = icmp eq ptr %266, null
  br i1 %267, label %if41, label %end42

if41:                                             ; preds = %if40
  br label %end73

end42:                                            ; preds = %if40
  %268 = load ptr, ptr %6, align 8
  %269 = getelementptr inbounds %RedBlackTree_rbNode, ptr %268, i32 0, i32 1
  %270 = load i32, ptr %269, align 4
  %271 = icmp eq i32 %270, 0
  br i1 %271, label %if43, label %end47

if43:                                             ; preds = %end42
  %272 = load i32, ptr %8, align 4
  %273 = sub nsw i32 %272, 1
  %274 = sext i32 %273 to i64
  %275 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %274
  %276 = load ptr, ptr %275, align 8
  %277 = getelementptr inbounds %RedBlackTree_rbNode, ptr %276, i32 0, i32 1
  store i32 0, ptr %277, align 4
  %278 = load ptr, ptr %6, align 8
  %279 = getelementptr inbounds %RedBlackTree_rbNode, ptr %278, i32 0, i32 1
  store i32 1, ptr %279, align 4
  %280 = load i32, ptr %8, align 4
  %281 = sub nsw i32 %280, 1
  %282 = sext i32 %281 to i64
  %283 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %282
  %284 = load ptr, ptr %283, align 8
  %285 = getelementptr inbounds %RedBlackTree_rbNode, ptr %284, i32 0, i32 2
  %286 = getelementptr inbounds [2 x ptr], ptr %285, i64 0, i64 1
  %287 = load ptr, ptr %6, align 8
  %288 = getelementptr inbounds %RedBlackTree_rbNode, ptr %287, i32 0, i32 2
  %289 = getelementptr inbounds [2 x ptr], ptr %288, i64 0, i64 0
  %290 = load ptr, ptr %289, align 8
  store ptr %290, ptr %286, align 8
  %291 = load ptr, ptr %6, align 8
  %292 = getelementptr inbounds %RedBlackTree_rbNode, ptr %291, i32 0, i32 2
  %293 = getelementptr inbounds [2 x ptr], ptr %292, i64 0, i64 0
  %294 = load i32, ptr %8, align 4
  %295 = sub nsw i32 %294, 1
  %296 = sext i32 %295 to i64
  %297 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %296
  %298 = load ptr, ptr %297, align 8
  store ptr %298, ptr %293, align 8
  %299 = load i32, ptr %8, align 4
  %300 = sub nsw i32 %299, 1
  %301 = sext i32 %300 to i64
  %302 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %301
  %303 = load ptr, ptr %302, align 8
  %304 = load ptr, ptr @RedBlackTree_root, align 8
  %305 = icmp eq ptr %303, %304
  br i1 %305, label %if44, label %else45

if44:                                             ; preds = %if43
  %306 = load ptr, ptr %6, align 8
  store ptr %306, ptr @RedBlackTree_root, align 8
  br label %end46

else45:                                           ; preds = %if43
  %307 = load i32, ptr %8, align 4
  %308 = sub nsw i32 %307, 2
  %309 = sext i32 %308 to i64
  %310 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %309
  %311 = load ptr, ptr %310, align 8
  %312 = getelementptr inbounds %RedBlackTree_rbNode, ptr %311, i32 0, i32 2
  %313 = load i32, ptr %8, align 4
  %314 = sub nsw i32 %313, 2
  %315 = sext i32 %314 to i64
  %316 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %315
  %317 = load i32, ptr %316, align 4
  %318 = sext i32 %317 to i64
  %319 = getelementptr inbounds [2 x ptr], ptr %312, i64 0, i64 %318
  %320 = load ptr, ptr %6, align 8
  store ptr %320, ptr %319, align 8
  br label %end46

end46:                                            ; preds = %else45, %if44
  %321 = load i32, ptr %8, align 4
  %322 = sext i32 %321 to i64
  %323 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %322
  store i32 0, ptr %323, align 4
  %324 = load i32, ptr %8, align 4
  %325 = sext i32 %324 to i64
  %326 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %325
  %327 = load i32, ptr %8, align 4
  %328 = sub nsw i32 %327, 1
  %329 = sext i32 %328 to i64
  %330 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %329
  %331 = load ptr, ptr %330, align 8
  store ptr %331, ptr %326, align 8
  %332 = load i32, ptr %8, align 4
  %333 = sub nsw i32 %332, 1
  %334 = sext i32 %333 to i64
  %335 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %334
  %336 = load ptr, ptr %6, align 8
  store ptr %336, ptr %335, align 8
  %337 = load i32, ptr %8, align 4
  %338 = add i32 %337, 1
  store i32 %338, ptr %8, align 4
  %339 = load i32, ptr %8, align 4
  %340 = sub nsw i32 %339, 1
  %341 = sext i32 %340 to i64
  %342 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %341
  %343 = load ptr, ptr %342, align 8
  %344 = getelementptr inbounds %RedBlackTree_rbNode, ptr %343, i32 0, i32 2
  %345 = getelementptr inbounds [2 x ptr], ptr %344, i64 0, i64 1
  %346 = load ptr, ptr %345, align 8
  store ptr %346, ptr %6, align 8
  br label %end47

end47:                                            ; preds = %end46, %end42
  %347 = load ptr, ptr %6, align 8
  %348 = getelementptr inbounds %RedBlackTree_rbNode, ptr %347, i32 0, i32 2
  %349 = getelementptr inbounds [2 x ptr], ptr %348, i64 0, i64 0
  %350 = load ptr, ptr %349, align 8
  %351 = icmp eq ptr %350, null
  %352 = load ptr, ptr %6, align 8
  %353 = getelementptr inbounds %RedBlackTree_rbNode, ptr %352, i32 0, i32 2
  %354 = getelementptr inbounds [2 x ptr], ptr %353, i64 0, i64 0
  %355 = load ptr, ptr %354, align 8
  %356 = getelementptr inbounds %RedBlackTree_rbNode, ptr %355, i32 0, i32 1
  %357 = load i32, ptr %356, align 4
  %358 = icmp eq i32 %357, 1
  %359 = select i1 %351, i1 true, i1 %358
  %360 = load ptr, ptr %6, align 8
  %361 = getelementptr inbounds %RedBlackTree_rbNode, ptr %360, i32 0, i32 2
  %362 = getelementptr inbounds [2 x ptr], ptr %361, i64 0, i64 1
  %363 = load ptr, ptr %362, align 8
  %364 = icmp eq ptr %363, null
  %365 = load ptr, ptr %6, align 8
  %366 = getelementptr inbounds %RedBlackTree_rbNode, ptr %365, i32 0, i32 2
  %367 = getelementptr inbounds [2 x ptr], ptr %366, i64 0, i64 1
  %368 = load ptr, ptr %367, align 8
  %369 = getelementptr inbounds %RedBlackTree_rbNode, ptr %368, i32 0, i32 1
  %370 = load i32, ptr %369, align 4
  %371 = icmp eq i32 %370, 1
  %372 = select i1 %364, i1 true, i1 %371
  %373 = select i1 %359, i1 %372, i1 false
  br i1 %373, label %if48, label %else49

if48:                                             ; preds = %end47
  %374 = load ptr, ptr %6, align 8
  %375 = getelementptr inbounds %RedBlackTree_rbNode, ptr %374, i32 0, i32 1
  store i32 0, ptr %375, align 4
  br label %end55

else49:                                           ; preds = %end47
  %376 = load ptr, ptr %6, align 8
  %377 = getelementptr inbounds %RedBlackTree_rbNode, ptr %376, i32 0, i32 2
  %378 = getelementptr inbounds [2 x ptr], ptr %377, i64 0, i64 1
  %379 = load ptr, ptr %378, align 8
  %380 = icmp eq ptr %379, null
  %381 = load ptr, ptr %6, align 8
  %382 = getelementptr inbounds %RedBlackTree_rbNode, ptr %381, i32 0, i32 2
  %383 = getelementptr inbounds [2 x ptr], ptr %382, i64 0, i64 1
  %384 = load ptr, ptr %383, align 8
  %385 = getelementptr inbounds %RedBlackTree_rbNode, ptr %384, i32 0, i32 1
  %386 = load i32, ptr %385, align 4
  %387 = icmp eq i32 %386, 1
  %388 = select i1 %380, i1 true, i1 %387
  br i1 %388, label %if50, label %end51

if50:                                             ; preds = %else49
  %389 = load ptr, ptr %6, align 8
  %390 = getelementptr inbounds %RedBlackTree_rbNode, ptr %389, i32 0, i32 2
  %391 = getelementptr inbounds [2 x ptr], ptr %390, i64 0, i64 0
  %392 = load ptr, ptr %391, align 8
  store ptr %392, ptr %5, align 8
  %393 = load ptr, ptr %6, align 8
  %394 = getelementptr inbounds %RedBlackTree_rbNode, ptr %393, i32 0, i32 1
  store i32 0, ptr %394, align 4
  %395 = load ptr, ptr %5, align 8
  %396 = getelementptr inbounds %RedBlackTree_rbNode, ptr %395, i32 0, i32 1
  store i32 1, ptr %396, align 4
  %397 = load ptr, ptr %6, align 8
  %398 = getelementptr inbounds %RedBlackTree_rbNode, ptr %397, i32 0, i32 2
  %399 = getelementptr inbounds [2 x ptr], ptr %398, i64 0, i64 0
  %400 = load ptr, ptr %5, align 8
  %401 = getelementptr inbounds %RedBlackTree_rbNode, ptr %400, i32 0, i32 2
  %402 = getelementptr inbounds [2 x ptr], ptr %401, i64 0, i64 1
  %403 = load ptr, ptr %402, align 8
  store ptr %403, ptr %399, align 8
  %404 = load ptr, ptr %5, align 8
  %405 = getelementptr inbounds %RedBlackTree_rbNode, ptr %404, i32 0, i32 2
  %406 = getelementptr inbounds [2 x ptr], ptr %405, i64 0, i64 1
  %407 = load ptr, ptr %6, align 8
  store ptr %407, ptr %406, align 8
  %408 = load i32, ptr %8, align 4
  %409 = sub nsw i32 %408, 1
  %410 = sext i32 %409 to i64
  %411 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %410
  %412 = load ptr, ptr %411, align 8
  %413 = getelementptr inbounds %RedBlackTree_rbNode, ptr %412, i32 0, i32 2
  %414 = getelementptr inbounds [2 x ptr], ptr %413, i64 0, i64 1
  %415 = load ptr, ptr %5, align 8
  store ptr %415, ptr %414, align 8
  %416 = load ptr, ptr %5, align 8
  store ptr %416, ptr %6, align 8
  br label %end51

end51:                                            ; preds = %if50, %else49
  %417 = load ptr, ptr %6, align 8
  %418 = getelementptr inbounds %RedBlackTree_rbNode, ptr %417, i32 0, i32 1
  %419 = load i32, ptr %8, align 4
  %420 = sub nsw i32 %419, 1
  %421 = sext i32 %420 to i64
  %422 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %421
  %423 = load ptr, ptr %422, align 8
  %424 = getelementptr inbounds %RedBlackTree_rbNode, ptr %423, i32 0, i32 1
  %425 = load i32, ptr %424, align 4
  store i32 %425, ptr %418, align 4
  %426 = load i32, ptr %8, align 4
  %427 = sub nsw i32 %426, 1
  %428 = sext i32 %427 to i64
  %429 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %428
  %430 = load ptr, ptr %429, align 8
  %431 = getelementptr inbounds %RedBlackTree_rbNode, ptr %430, i32 0, i32 1
  store i32 1, ptr %431, align 4
  %432 = load ptr, ptr %6, align 8
  %433 = getelementptr inbounds %RedBlackTree_rbNode, ptr %432, i32 0, i32 2
  %434 = getelementptr inbounds [2 x ptr], ptr %433, i64 0, i64 1
  %435 = load ptr, ptr %434, align 8
  %436 = getelementptr inbounds %RedBlackTree_rbNode, ptr %435, i32 0, i32 1
  store i32 1, ptr %436, align 4
  %437 = load i32, ptr %8, align 4
  %438 = sub nsw i32 %437, 1
  %439 = sext i32 %438 to i64
  %440 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %439
  %441 = load ptr, ptr %440, align 8
  %442 = getelementptr inbounds %RedBlackTree_rbNode, ptr %441, i32 0, i32 2
  %443 = getelementptr inbounds [2 x ptr], ptr %442, i64 0, i64 1
  %444 = load ptr, ptr %6, align 8
  %445 = getelementptr inbounds %RedBlackTree_rbNode, ptr %444, i32 0, i32 2
  %446 = getelementptr inbounds [2 x ptr], ptr %445, i64 0, i64 0
  %447 = load ptr, ptr %446, align 8
  store ptr %447, ptr %443, align 8
  %448 = load ptr, ptr %6, align 8
  %449 = getelementptr inbounds %RedBlackTree_rbNode, ptr %448, i32 0, i32 2
  %450 = getelementptr inbounds [2 x ptr], ptr %449, i64 0, i64 0
  %451 = load i32, ptr %8, align 4
  %452 = sub nsw i32 %451, 1
  %453 = sext i32 %452 to i64
  %454 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %453
  %455 = load ptr, ptr %454, align 8
  store ptr %455, ptr %450, align 8
  %456 = load i32, ptr %8, align 4
  %457 = sub nsw i32 %456, 1
  %458 = sext i32 %457 to i64
  %459 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %458
  %460 = load ptr, ptr %459, align 8
  %461 = load ptr, ptr @RedBlackTree_root, align 8
  %462 = icmp eq ptr %460, %461
  br i1 %462, label %if52, label %else53

if52:                                             ; preds = %end51
  %463 = load ptr, ptr %6, align 8
  store ptr %463, ptr @RedBlackTree_root, align 8
  br label %end54

else53:                                           ; preds = %end51
  %464 = load i32, ptr %8, align 4
  %465 = sub nsw i32 %464, 2
  %466 = sext i32 %465 to i64
  %467 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %466
  %468 = load ptr, ptr %467, align 8
  %469 = getelementptr inbounds %RedBlackTree_rbNode, ptr %468, i32 0, i32 2
  %470 = load i32, ptr %8, align 4
  %471 = sub nsw i32 %470, 2
  %472 = sext i32 %471 to i64
  %473 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %472
  %474 = load i32, ptr %473, align 4
  %475 = sext i32 %474 to i64
  %476 = getelementptr inbounds [2 x ptr], ptr %469, i64 0, i64 %475
  %477 = load ptr, ptr %6, align 8
  store ptr %477, ptr %476, align 8
  br label %end54

end54:                                            ; preds = %else53, %if52
  br label %end73

end55:                                            ; preds = %if48
  br label %end72

else56:                                           ; preds = %end39
  %478 = load i32, ptr %8, align 4
  %479 = sub nsw i32 %478, 1
  %480 = sext i32 %479 to i64
  %481 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %480
  %482 = load ptr, ptr %481, align 8
  %483 = getelementptr inbounds %RedBlackTree_rbNode, ptr %482, i32 0, i32 2
  %484 = getelementptr inbounds [2 x ptr], ptr %483, i64 0, i64 0
  %485 = load ptr, ptr %484, align 8
  store ptr %485, ptr %6, align 8
  %486 = load ptr, ptr %6, align 8
  %487 = icmp eq ptr %486, null
  br i1 %487, label %if57, label %end58

if57:                                             ; preds = %else56
  br label %end73

end58:                                            ; preds = %else56
  %488 = load ptr, ptr %6, align 8
  %489 = getelementptr inbounds %RedBlackTree_rbNode, ptr %488, i32 0, i32 1
  %490 = load i32, ptr %489, align 4
  %491 = icmp eq i32 %490, 0
  br i1 %491, label %if59, label %end63

if59:                                             ; preds = %end58
  %492 = load i32, ptr %8, align 4
  %493 = sub nsw i32 %492, 1
  %494 = sext i32 %493 to i64
  %495 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %494
  %496 = load ptr, ptr %495, align 8
  %497 = getelementptr inbounds %RedBlackTree_rbNode, ptr %496, i32 0, i32 1
  store i32 0, ptr %497, align 4
  %498 = load ptr, ptr %6, align 8
  %499 = getelementptr inbounds %RedBlackTree_rbNode, ptr %498, i32 0, i32 1
  store i32 1, ptr %499, align 4
  %500 = load i32, ptr %8, align 4
  %501 = sub nsw i32 %500, 1
  %502 = sext i32 %501 to i64
  %503 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %502
  %504 = load ptr, ptr %503, align 8
  %505 = getelementptr inbounds %RedBlackTree_rbNode, ptr %504, i32 0, i32 2
  %506 = getelementptr inbounds [2 x ptr], ptr %505, i64 0, i64 0
  %507 = load ptr, ptr %6, align 8
  %508 = getelementptr inbounds %RedBlackTree_rbNode, ptr %507, i32 0, i32 2
  %509 = getelementptr inbounds [2 x ptr], ptr %508, i64 0, i64 1
  %510 = load ptr, ptr %509, align 8
  store ptr %510, ptr %506, align 8
  %511 = load ptr, ptr %6, align 8
  %512 = getelementptr inbounds %RedBlackTree_rbNode, ptr %511, i32 0, i32 2
  %513 = getelementptr inbounds [2 x ptr], ptr %512, i64 0, i64 1
  %514 = load i32, ptr %8, align 4
  %515 = sub nsw i32 %514, 1
  %516 = sext i32 %515 to i64
  %517 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %516
  %518 = load ptr, ptr %517, align 8
  store ptr %518, ptr %513, align 8
  %519 = load i32, ptr %8, align 4
  %520 = sub nsw i32 %519, 1
  %521 = sext i32 %520 to i64
  %522 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %521
  %523 = load ptr, ptr %522, align 8
  %524 = load ptr, ptr @RedBlackTree_root, align 8
  %525 = icmp eq ptr %523, %524
  br i1 %525, label %if60, label %else61

if60:                                             ; preds = %if59
  %526 = load ptr, ptr %6, align 8
  store ptr %526, ptr @RedBlackTree_root, align 8
  br label %end62

else61:                                           ; preds = %if59
  %527 = load i32, ptr %8, align 4
  %528 = sub nsw i32 %527, 2
  %529 = sext i32 %528 to i64
  %530 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %529
  %531 = load ptr, ptr %530, align 8
  %532 = getelementptr inbounds %RedBlackTree_rbNode, ptr %531, i32 0, i32 2
  %533 = load i32, ptr %8, align 4
  %534 = sub nsw i32 %533, 2
  %535 = sext i32 %534 to i64
  %536 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %535
  %537 = load i32, ptr %536, align 4
  %538 = sext i32 %537 to i64
  %539 = getelementptr inbounds [2 x ptr], ptr %532, i64 0, i64 %538
  %540 = load ptr, ptr %6, align 8
  store ptr %540, ptr %539, align 8
  br label %end62

end62:                                            ; preds = %else61, %if60
  %541 = load i32, ptr %8, align 4
  %542 = sext i32 %541 to i64
  %543 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %542
  store i32 1, ptr %543, align 4
  %544 = load i32, ptr %8, align 4
  %545 = sext i32 %544 to i64
  %546 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %545
  %547 = load i32, ptr %8, align 4
  %548 = sub nsw i32 %547, 1
  %549 = sext i32 %548 to i64
  %550 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %549
  %551 = load ptr, ptr %550, align 8
  store ptr %551, ptr %546, align 8
  %552 = load i32, ptr %8, align 4
  %553 = sub nsw i32 %552, 1
  %554 = sext i32 %553 to i64
  %555 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %554
  %556 = load ptr, ptr %6, align 8
  store ptr %556, ptr %555, align 8
  %557 = load i32, ptr %8, align 4
  %558 = add i32 %557, 1
  store i32 %558, ptr %8, align 4
  %559 = load i32, ptr %8, align 4
  %560 = sub nsw i32 %559, 1
  %561 = sext i32 %560 to i64
  %562 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %561
  %563 = load ptr, ptr %562, align 8
  %564 = getelementptr inbounds %RedBlackTree_rbNode, ptr %563, i32 0, i32 2
  %565 = getelementptr inbounds [2 x ptr], ptr %564, i64 0, i64 0
  %566 = load ptr, ptr %565, align 8
  store ptr %566, ptr %6, align 8
  br label %end63

end63:                                            ; preds = %end62, %end58
  %567 = load ptr, ptr %6, align 8
  %568 = getelementptr inbounds %RedBlackTree_rbNode, ptr %567, i32 0, i32 2
  %569 = getelementptr inbounds [2 x ptr], ptr %568, i64 0, i64 0
  %570 = load ptr, ptr %569, align 8
  %571 = icmp ne ptr %570, null
  %572 = xor i1 %571, true
  %573 = load ptr, ptr %6, align 8
  %574 = getelementptr inbounds %RedBlackTree_rbNode, ptr %573, i32 0, i32 2
  %575 = getelementptr inbounds [2 x ptr], ptr %574, i64 0, i64 0
  %576 = load ptr, ptr %575, align 8
  %577 = getelementptr inbounds %RedBlackTree_rbNode, ptr %576, i32 0, i32 1
  %578 = load i32, ptr %577, align 4
  %579 = icmp eq i32 %578, 1
  %580 = select i1 %572, i1 true, i1 %579
  %581 = load ptr, ptr %6, align 8
  %582 = getelementptr inbounds %RedBlackTree_rbNode, ptr %581, i32 0, i32 2
  %583 = getelementptr inbounds [2 x ptr], ptr %582, i64 0, i64 1
  %584 = load ptr, ptr %583, align 8
  %585 = icmp ne ptr %584, null
  %586 = xor i1 %585, true
  %587 = load ptr, ptr %6, align 8
  %588 = getelementptr inbounds %RedBlackTree_rbNode, ptr %587, i32 0, i32 2
  %589 = getelementptr inbounds [2 x ptr], ptr %588, i64 0, i64 1
  %590 = load ptr, ptr %589, align 8
  %591 = getelementptr inbounds %RedBlackTree_rbNode, ptr %590, i32 0, i32 1
  %592 = load i32, ptr %591, align 4
  %593 = icmp eq i32 %592, 1
  %594 = select i1 %586, i1 true, i1 %593
  %595 = select i1 %580, i1 %594, i1 false
  br i1 %595, label %if64, label %else65

if64:                                             ; preds = %end63
  %596 = load ptr, ptr %6, align 8
  %597 = getelementptr inbounds %RedBlackTree_rbNode, ptr %596, i32 0, i32 1
  store i32 0, ptr %597, align 4
  br label %end71

else65:                                           ; preds = %end63
  %598 = load ptr, ptr %6, align 8
  %599 = getelementptr inbounds %RedBlackTree_rbNode, ptr %598, i32 0, i32 2
  %600 = getelementptr inbounds [2 x ptr], ptr %599, i64 0, i64 0
  %601 = load ptr, ptr %600, align 8
  %602 = icmp ne ptr %601, null
  %603 = xor i1 %602, true
  %604 = load ptr, ptr %6, align 8
  %605 = getelementptr inbounds %RedBlackTree_rbNode, ptr %604, i32 0, i32 2
  %606 = getelementptr inbounds [2 x ptr], ptr %605, i64 0, i64 0
  %607 = load ptr, ptr %606, align 8
  %608 = getelementptr inbounds %RedBlackTree_rbNode, ptr %607, i32 0, i32 1
  %609 = load i32, ptr %608, align 4
  %610 = icmp eq i32 %609, 1
  %611 = select i1 %603, i1 true, i1 %610
  br i1 %611, label %if66, label %end67

if66:                                             ; preds = %else65
  %612 = load ptr, ptr %6, align 8
  %613 = getelementptr inbounds %RedBlackTree_rbNode, ptr %612, i32 0, i32 2
  %614 = getelementptr inbounds [2 x ptr], ptr %613, i64 0, i64 1
  %615 = load ptr, ptr %614, align 8
  store ptr %615, ptr %5, align 8
  %616 = load ptr, ptr %6, align 8
  %617 = getelementptr inbounds %RedBlackTree_rbNode, ptr %616, i32 0, i32 1
  store i32 0, ptr %617, align 4
  %618 = load ptr, ptr %5, align 8
  %619 = getelementptr inbounds %RedBlackTree_rbNode, ptr %618, i32 0, i32 1
  store i32 1, ptr %619, align 4
  %620 = load ptr, ptr %6, align 8
  %621 = getelementptr inbounds %RedBlackTree_rbNode, ptr %620, i32 0, i32 2
  %622 = getelementptr inbounds [2 x ptr], ptr %621, i64 0, i64 1
  %623 = load ptr, ptr %5, align 8
  %624 = getelementptr inbounds %RedBlackTree_rbNode, ptr %623, i32 0, i32 2
  %625 = getelementptr inbounds [2 x ptr], ptr %624, i64 0, i64 0
  %626 = load ptr, ptr %625, align 8
  store ptr %626, ptr %622, align 8
  %627 = load ptr, ptr %5, align 8
  %628 = getelementptr inbounds %RedBlackTree_rbNode, ptr %627, i32 0, i32 2
  %629 = getelementptr inbounds [2 x ptr], ptr %628, i64 0, i64 0
  %630 = load ptr, ptr %6, align 8
  store ptr %630, ptr %629, align 8
  %631 = load i32, ptr %8, align 4
  %632 = sub nsw i32 %631, 1
  %633 = sext i32 %632 to i64
  %634 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %633
  %635 = load ptr, ptr %634, align 8
  %636 = getelementptr inbounds %RedBlackTree_rbNode, ptr %635, i32 0, i32 2
  %637 = getelementptr inbounds [2 x ptr], ptr %636, i64 0, i64 0
  %638 = load ptr, ptr %5, align 8
  store ptr %638, ptr %637, align 8
  %639 = load ptr, ptr %5, align 8
  store ptr %639, ptr %6, align 8
  br label %end67

end67:                                            ; preds = %if66, %else65
  %640 = load ptr, ptr %6, align 8
  %641 = getelementptr inbounds %RedBlackTree_rbNode, ptr %640, i32 0, i32 1
  %642 = load i32, ptr %8, align 4
  %643 = sub nsw i32 %642, 1
  %644 = sext i32 %643 to i64
  %645 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %644
  %646 = load ptr, ptr %645, align 8
  %647 = getelementptr inbounds %RedBlackTree_rbNode, ptr %646, i32 0, i32 1
  %648 = load i32, ptr %647, align 4
  store i32 %648, ptr %641, align 4
  %649 = load i32, ptr %8, align 4
  %650 = sub nsw i32 %649, 1
  %651 = sext i32 %650 to i64
  %652 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %651
  %653 = load ptr, ptr %652, align 8
  %654 = getelementptr inbounds %RedBlackTree_rbNode, ptr %653, i32 0, i32 1
  store i32 1, ptr %654, align 4
  %655 = load ptr, ptr %6, align 8
  %656 = getelementptr inbounds %RedBlackTree_rbNode, ptr %655, i32 0, i32 2
  %657 = getelementptr inbounds [2 x ptr], ptr %656, i64 0, i64 0
  %658 = load ptr, ptr %657, align 8
  %659 = getelementptr inbounds %RedBlackTree_rbNode, ptr %658, i32 0, i32 1
  store i32 1, ptr %659, align 4
  %660 = load i32, ptr %8, align 4
  %661 = sub nsw i32 %660, 1
  %662 = sext i32 %661 to i64
  %663 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %662
  %664 = load ptr, ptr %663, align 8
  %665 = getelementptr inbounds %RedBlackTree_rbNode, ptr %664, i32 0, i32 2
  %666 = getelementptr inbounds [2 x ptr], ptr %665, i64 0, i64 0
  %667 = load ptr, ptr %6, align 8
  %668 = getelementptr inbounds %RedBlackTree_rbNode, ptr %667, i32 0, i32 2
  %669 = getelementptr inbounds [2 x ptr], ptr %668, i64 0, i64 1
  %670 = load ptr, ptr %669, align 8
  store ptr %670, ptr %666, align 8
  %671 = load ptr, ptr %6, align 8
  %672 = getelementptr inbounds %RedBlackTree_rbNode, ptr %671, i32 0, i32 2
  %673 = getelementptr inbounds [2 x ptr], ptr %672, i64 0, i64 1
  %674 = load i32, ptr %8, align 4
  %675 = sub nsw i32 %674, 1
  %676 = sext i32 %675 to i64
  %677 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %676
  %678 = load ptr, ptr %677, align 8
  store ptr %678, ptr %673, align 8
  %679 = load i32, ptr %8, align 4
  %680 = sub nsw i32 %679, 1
  %681 = sext i32 %680 to i64
  %682 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %681
  %683 = load ptr, ptr %682, align 8
  %684 = load ptr, ptr @RedBlackTree_root, align 8
  %685 = icmp eq ptr %683, %684
  br i1 %685, label %if68, label %else69

if68:                                             ; preds = %end67
  %686 = load ptr, ptr %6, align 8
  store ptr %686, ptr @RedBlackTree_root, align 8
  br label %end70

else69:                                           ; preds = %end67
  %687 = load i32, ptr %8, align 4
  %688 = sub nsw i32 %687, 2
  %689 = sext i32 %688 to i64
  %690 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %689
  %691 = load ptr, ptr %690, align 8
  %692 = getelementptr inbounds %RedBlackTree_rbNode, ptr %691, i32 0, i32 2
  %693 = load i32, ptr %8, align 4
  %694 = sub nsw i32 %693, 2
  %695 = sext i32 %694 to i64
  %696 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %695
  %697 = load i32, ptr %696, align 4
  %698 = sext i32 %697 to i64
  %699 = getelementptr inbounds [2 x ptr], ptr %692, i64 0, i64 %698
  %700 = load ptr, ptr %6, align 8
  store ptr %700, ptr %699, align 8
  br label %end70

end70:                                            ; preds = %else69, %if68
  br label %end73

end71:                                            ; preds = %if64
  br label %end72

end72:                                            ; preds = %end71, %end55
  %701 = load i32, ptr %8, align 4
  %702 = sub i32 %701, 1
  store i32 %702, ptr %8, align 4
  br label %cond34

end73:                                            ; preds = %end70, %if57, %end54, %if41, %if38, %if36, %cond34
  br label %end74

end74:                                            ; preds = %end73, %end32
  ret void
}
