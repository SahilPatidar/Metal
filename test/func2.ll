
define void @tbttest_deletion(i32 %tbttest_data) {
entry:
  %tbttest_data1 = alloca i32, align 4
  store i32 %tbttest_data, ptr %tbttest_data1, align 4
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
  %12 = load ptr, ptr @tbttest_root, align 8
  store ptr %12, ptr %1, align 8
  %13 = load ptr, ptr %1, align 8
  %14 = getelementptr inbounds %tbttest_rbNode, ptr %13, i32 0, i32 1
  %15 = load i32, ptr %14, align 4
  %16 = icmp eq i32 %15, 1
  br i1 %16, label %if, label %end22

if:                                               ; preds = %entry
  br label %cond

cond:                                             ; preds = %end20, %if
  br i1 true, label %loop, label %end21

loop:                                             ; preds = %cond
  %17 = load i32, ptr %8, align 4
  %18 = sub nsw i32 %17, 1
  %19 = sext i32 %18 to i64
  %20 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %19
  %21 = load ptr, ptr %20, align 8
  %22 = getelementptr inbounds %tbttest_rbNode, ptr %21, i32 0, i32 2
  %23 = load i32, ptr %8, align 4
  %24 = sub nsw i32 %23, 1
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %25
  %27 = load i32, ptr %26, align 4
  %28 = sext i32 %27 to i64
  %29 = getelementptr inbounds [2 x ptr], ptr %22, i64 0, i64 %28
  %30 = load ptr, ptr %29, align 8
  store ptr %30, ptr %4, align 8
  %31 = load ptr, ptr %4, align 8
  %32 = icmp ne ptr %31, null
  %33 = load ptr, ptr %4, align 8
  %34 = getelementptr inbounds %tbttest_rbNode, ptr %33, i32 0, i32 1
  %35 = load i32, ptr %34, align 4
  %36 = icmp eq i32 %35, 0
  %37 = select i1 %32, i1 %36, i1 false
  br i1 %37, label %if2, label %end

if2:                                              ; preds = %loop
  %38 = load ptr, ptr %4, align 8
  %39 = getelementptr inbounds %tbttest_rbNode, ptr %38, i32 0, i32 1
  store i32 1, ptr %39, align 4
  br label %end21

end:                                              ; preds = %loop
  %40 = load i32, ptr %8, align 4
  %41 = icmp slt i32 %40, 2
  br i1 %41, label %if3, label %end4

if3:                                              ; preds = %end
  br label %end21

end4:                                             ; preds = %end
  %42 = load i32, ptr %8, align 4
  %43 = sub nsw i32 %42, 2
  %44 = sext i32 %43 to i64
  %45 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %44
  %46 = load i32, ptr %45, align 4
  %47 = icmp eq i32 %46, 0
  br i1 %47, label %if5, label %end20

if5:                                              ; preds = %end4
  %48 = load i32, ptr %8, align 4
  %49 = sub nsw i32 %48, 1
  %50 = sext i32 %49 to i64
  %51 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %50
  %52 = load ptr, ptr %51, align 8
  %53 = getelementptr inbounds %tbttest_rbNode, ptr %52, i32 0, i32 2
  %54 = getelementptr inbounds [2 x ptr], ptr %53, i64 0, i64 1
  %55 = load ptr, ptr %54, align 8
  store ptr %55, ptr %6, align 8
  %56 = load ptr, ptr %6, align 8
  %57 = icmp eq ptr %56, null
  br i1 %57, label %if6, label %end7

if6:                                              ; preds = %if5
  br label %end21

end7:                                             ; preds = %if5
  %58 = load ptr, ptr %6, align 8
  %59 = getelementptr inbounds %tbttest_rbNode, ptr %58, i32 0, i32 1
  %60 = load i32, ptr %59, align 4
  %61 = icmp eq i32 %60, 0
  br i1 %61, label %if8, label %end11

if8:                                              ; preds = %end7
  %62 = load i32, ptr %8, align 4
  %63 = sub nsw i32 %62, 1
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %64
  %66 = load ptr, ptr %65, align 8
  %67 = getelementptr inbounds %tbttest_rbNode, ptr %66, i32 0, i32 1
  store i32 0, ptr %67, align 4
  %68 = load ptr, ptr %6, align 8
  %69 = getelementptr inbounds %tbttest_rbNode, ptr %68, i32 0, i32 1
  store i32 1, ptr %69, align 4
  %70 = load i32, ptr %8, align 4
  %71 = sub nsw i32 %70, 1
  %72 = sext i32 %71 to i64
  %73 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %72
  %74 = load ptr, ptr %73, align 8
  %75 = getelementptr inbounds %tbttest_rbNode, ptr %74, i32 0, i32 2
  %76 = getelementptr inbounds [2 x ptr], ptr %75, i64 0, i64 1
  %77 = load ptr, ptr %6, align 8
  %78 = getelementptr inbounds %tbttest_rbNode, ptr %77, i32 0, i32 2
  %79 = getelementptr inbounds [2 x ptr], ptr %78, i64 0, i64 0
  %80 = load ptr, ptr %79, align 8
  store ptr %80, ptr %76, align 8
  %81 = load ptr, ptr %6, align 8
  %82 = getelementptr inbounds %tbttest_rbNode, ptr %81, i32 0, i32 2
  %83 = getelementptr inbounds [2 x ptr], ptr %82, i64 0, i64 0
  %84 = load i32, ptr %8, align 4
  %85 = sub nsw i32 %84, 1
  %86 = sext i32 %85 to i64
  %87 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %86
  %88 = load ptr, ptr %87, align 8
  store ptr %88, ptr %83, align 8
  %89 = load i32, ptr %8, align 4
  %90 = sub nsw i32 %89, 1
  %91 = sext i32 %90 to i64
  %92 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %91
  %93 = load ptr, ptr %92, align 8
  %94 = load ptr, ptr @tbttest_root, align 8
  %95 = icmp eq ptr %93, %94
  br i1 %95, label %if9, label %else

if9:                                              ; preds = %if8
  %96 = load ptr, ptr %6, align 8
  store ptr %96, ptr @tbttest_root, align 8
  br label %end10

else:                                             ; preds = %if8
  %97 = load i32, ptr %8, align 4
  %98 = sub nsw i32 %97, 2
  %99 = sext i32 %98 to i64
  %100 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %99
  %101 = load ptr, ptr %100, align 8
  %102 = getelementptr inbounds %tbttest_rbNode, ptr %101, i32 0, i32 2
  %103 = load i32, ptr %8, align 4
  %104 = sub nsw i32 %103, 2
  %105 = sext i32 %104 to i64
  %106 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %105
  %107 = load i32, ptr %106, align 4
  %108 = sext i32 %107 to i64
  %109 = getelementptr inbounds [2 x ptr], ptr %102, i64 0, i64 %108
  %110 = load ptr, ptr %6, align 8
  store ptr %110, ptr %109, align 8
  br label %end10

end10:                                            ; preds = %else, %if9
  %111 = load i32, ptr %8, align 4
  %112 = sext i32 %111 to i64
  %113 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %112
  store i32 0, ptr %113, align 4
  %114 = load i32, ptr %8, align 4
  %115 = sext i32 %114 to i64
  %116 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %115
  %117 = load i32, ptr %8, align 4
  %118 = sub nsw i32 %117, 1
  %119 = sext i32 %118 to i64
  %120 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %119
  %121 = load ptr, ptr %120, align 8
  store ptr %121, ptr %116, align 8
  %122 = load i32, ptr %8, align 4
  %123 = sub nsw i32 %122, 1
  %124 = sext i32 %123 to i64
  %125 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %124
  %126 = load ptr, ptr %6, align 8
  store ptr %126, ptr %125, align 8
  %127 = load i32, ptr %8, align 4
  %128 = add i32 %127, 1
  store i32 %128, ptr %8, align 4
  %129 = load i32, ptr %8, align 4
  %130 = sub nsw i32 %129, 1
  %131 = sext i32 %130 to i64
  %132 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %131
  %133 = load ptr, ptr %132, align 8
  %134 = getelementptr inbounds %tbttest_rbNode, ptr %133, i32 0, i32 2
  %135 = getelementptr inbounds [2 x ptr], ptr %134, i64 0, i64 1
  %136 = load ptr, ptr %135, align 8
  store ptr %136, ptr %6, align 8
  br label %end11

end11:                                            ; preds = %end10, %end7
  %137 = load ptr, ptr %6, align 8
  %138 = getelementptr inbounds %tbttest_rbNode, ptr %137, i32 0, i32 2
  %139 = getelementptr inbounds [2 x ptr], ptr %138, i64 0, i64 0
  %140 = load ptr, ptr %139, align 8
  %141 = icmp eq ptr %140, null
  %142 = load ptr, ptr %6, align 8
  %143 = getelementptr inbounds %tbttest_rbNode, ptr %142, i32 0, i32 2
  %144 = getelementptr inbounds [2 x ptr], ptr %143, i64 0, i64 0
  %145 = load ptr, ptr %144, align 8
  %146 = getelementptr inbounds %tbttest_rbNode, ptr %145, i32 0, i32 1
  %147 = load i32, ptr %146, align 4
  %148 = icmp eq i32 %147, 1
  %149 = select i1 %141, i1 true, i1 %148
  %150 = load ptr, ptr %6, align 8
  %151 = getelementptr inbounds %tbttest_rbNode, ptr %150, i32 0, i32 2
  %152 = getelementptr inbounds [2 x ptr], ptr %151, i64 0, i64 1
  %153 = load ptr, ptr %152, align 8
  %154 = icmp eq ptr %153, null
  %155 = load ptr, ptr %6, align 8
  %156 = getelementptr inbounds %tbttest_rbNode, ptr %155, i32 0, i32 2
  %157 = getelementptr inbounds [2 x ptr], ptr %156, i64 0, i64 1
  %158 = load ptr, ptr %157, align 8
  %159 = getelementptr inbounds %tbttest_rbNode, ptr %158, i32 0, i32 1
  %160 = load i32, ptr %159, align 4
  %161 = icmp eq i32 %160, 1
  %162 = select i1 %154, i1 true, i1 %161
  %163 = select i1 %149, i1 %162, i1 false
  br i1 %163, label %if12, label %else13

if12:                                             ; preds = %end11
  %164 = load ptr, ptr %6, align 8
  %165 = getelementptr inbounds %tbttest_rbNode, ptr %164, i32 0, i32 1
  store i32 0, ptr %165, align 4
  br label %end19

else13:                                           ; preds = %end11
  %166 = load ptr, ptr %6, align 8
  %167 = getelementptr inbounds %tbttest_rbNode, ptr %166, i32 0, i32 2
  %168 = getelementptr inbounds [2 x ptr], ptr %167, i64 0, i64 1
  %169 = load ptr, ptr %168, align 8
  %170 = icmp eq ptr %169, null
  %171 = load ptr, ptr %6, align 8
  %172 = getelementptr inbounds %tbttest_rbNode, ptr %171, i32 0, i32 2
  %173 = getelementptr inbounds [2 x ptr], ptr %172, i64 0, i64 1
  %174 = load ptr, ptr %173, align 8
  %175 = getelementptr inbounds %tbttest_rbNode, ptr %174, i32 0, i32 1
  %176 = load i32, ptr %175, align 4
  %177 = icmp eq i32 %176, 1
  %178 = select i1 %170, i1 true, i1 %177
  br i1 %178, label %if14, label %end15

if14:                                             ; preds = %else13
  %179 = load ptr, ptr %6, align 8
  %180 = getelementptr inbounds %tbttest_rbNode, ptr %179, i32 0, i32 2
  %181 = getelementptr inbounds [2 x ptr], ptr %180, i64 0, i64 0
  %182 = load ptr, ptr %181, align 8
  store ptr %182, ptr %5, align 8
  %183 = load ptr, ptr %6, align 8
  %184 = getelementptr inbounds %tbttest_rbNode, ptr %183, i32 0, i32 1
  store i32 0, ptr %184, align 4
  %185 = load ptr, ptr %5, align 8
  %186 = getelementptr inbounds %tbttest_rbNode, ptr %185, i32 0, i32 1
  store i32 1, ptr %186, align 4
  %187 = load ptr, ptr %6, align 8
  %188 = getelementptr inbounds %tbttest_rbNode, ptr %187, i32 0, i32 2
  %189 = getelementptr inbounds [2 x ptr], ptr %188, i64 0, i64 0
  %190 = load ptr, ptr %5, align 8
  %191 = getelementptr inbounds %tbttest_rbNode, ptr %190, i32 0, i32 2
  %192 = getelementptr inbounds [2 x ptr], ptr %191, i64 0, i64 1
  %193 = load ptr, ptr %192, align 8
  store ptr %193, ptr %189, align 8
  %194 = load ptr, ptr %5, align 8
  %195 = getelementptr inbounds %tbttest_rbNode, ptr %194, i32 0, i32 2
  %196 = getelementptr inbounds [2 x ptr], ptr %195, i64 0, i64 1
  %197 = load ptr, ptr %6, align 8
  store ptr %197, ptr %196, align 8
  %198 = load i32, ptr %8, align 4
  %199 = sub nsw i32 %198, 1
  %200 = sext i32 %199 to i64
  %201 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %200
  %202 = load ptr, ptr %201, align 8
  %203 = getelementptr inbounds %tbttest_rbNode, ptr %202, i32 0, i32 2
  %204 = getelementptr inbounds [2 x ptr], ptr %203, i64 0, i64 1
  %205 = load ptr, ptr %5, align 8
  store ptr %205, ptr %204, align 8
  %206 = load ptr, ptr %5, align 8
  store ptr %206, ptr %6, align 8
  br label %end15

end15:                                            ; preds = %if14, %else13
  %207 = load ptr, ptr %6, align 8
  %208 = getelementptr inbounds %tbttest_rbNode, ptr %207, i32 0, i32 1
  %209 = load i32, ptr %8, align 4
  %210 = sub nsw i32 %209, 1
  %211 = sext i32 %210 to i64
  %212 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %211
  %213 = load ptr, ptr %212, align 8
  %214 = getelementptr inbounds %tbttest_rbNode, ptr %213, i32 0, i32 1
  %215 = load i32, ptr %214, align 4
  store i32 %215, ptr %208, align 4
  %216 = load i32, ptr %8, align 4
  %217 = sub nsw i32 %216, 1
  %218 = sext i32 %217 to i64
  %219 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %218
  %220 = load ptr, ptr %219, align 8
  %221 = getelementptr inbounds %tbttest_rbNode, ptr %220, i32 0, i32 1
  store i32 1, ptr %221, align 4
  %222 = load ptr, ptr %6, align 8
  %223 = getelementptr inbounds %tbttest_rbNode, ptr %222, i32 0, i32 2
  %224 = getelementptr inbounds [2 x ptr], ptr %223, i64 0, i64 1
  %225 = load ptr, ptr %224, align 8
  %226 = getelementptr inbounds %tbttest_rbNode, ptr %225, i32 0, i32 1
  store i32 1, ptr %226, align 4
  %227 = load i32, ptr %8, align 4
  %228 = sub nsw i32 %227, 1
  %229 = sext i32 %228 to i64
  %230 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %229
  %231 = load ptr, ptr %230, align 8
  %232 = getelementptr inbounds %tbttest_rbNode, ptr %231, i32 0, i32 2
  %233 = getelementptr inbounds [2 x ptr], ptr %232, i64 0, i64 1
  %234 = load ptr, ptr %6, align 8
  %235 = getelementptr inbounds %tbttest_rbNode, ptr %234, i32 0, i32 2
  %236 = getelementptr inbounds [2 x ptr], ptr %235, i64 0, i64 0
  %237 = load ptr, ptr %236, align 8
  store ptr %237, ptr %233, align 8
  %238 = load ptr, ptr %6, align 8
  %239 = getelementptr inbounds %tbttest_rbNode, ptr %238, i32 0, i32 2
  %240 = getelementptr inbounds [2 x ptr], ptr %239, i64 0, i64 0
  %241 = load i32, ptr %8, align 4
  %242 = sub nsw i32 %241, 1
  %243 = sext i32 %242 to i64
  %244 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %243
  %245 = load ptr, ptr %244, align 8
  store ptr %245, ptr %240, align 8
  %246 = load i32, ptr %8, align 4
  %247 = sub nsw i32 %246, 1
  %248 = sext i32 %247 to i64
  %249 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %248
  %250 = load ptr, ptr %249, align 8
  %251 = load ptr, ptr @tbttest_root, align 8
  %252 = icmp eq ptr %250, %251
  br i1 %252, label %if16, label %else17

if16:                                             ; preds = %end15
  %253 = load ptr, ptr %6, align 8
  store ptr %253, ptr @tbttest_root, align 8
  br label %end18

else17:                                           ; preds = %end15
  %254 = load i32, ptr %8, align 4
  %255 = sub nsw i32 %254, 2
  %256 = sext i32 %255 to i64
  %257 = getelementptr inbounds [98 x ptr], ptr %0, i64 0, i64 %256
  %258 = load ptr, ptr %257, align 8
  %259 = getelementptr inbounds %tbttest_rbNode, ptr %258, i32 0, i32 2
  %260 = load i32, ptr %8, align 4
  %261 = sub nsw i32 %260, 2
  %262 = sext i32 %261 to i64
  %263 = getelementptr inbounds [98 x i32], ptr %7, i64 0, i64 %262
  %264 = load i32, ptr %263, align 4
  %265 = sext i32 %264 to i64
  %266 = getelementptr inbounds [2 x ptr], ptr %259, i64 0, i64 %265
  %267 = load ptr, ptr %6, align 8
  store ptr %267, ptr %266, align 8
  br label %end18

end18:                                            ; preds = %else17, %if16
  br label %end21

end19:                                            ; preds = %if12
  br label %end20

end20:                                            ; preds = %end19, %end4
  %268 = load i32, ptr %8, align 4
  %269 = sub i32 %268, 1
  store i32 %269, ptr %8, align 4
  br label %cond

end21:                                            ; preds = %end18, %if6, %if3, %if2, %cond
  br label %end22

end22:                                            ; preds = %end21, %entry
  ret void
}