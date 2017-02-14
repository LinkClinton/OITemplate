# 草稿本

设序列为[l,r]
然后设切割点的位置为x,y。并且x<=y。

我们设先切割x的贡献为:
	S_x=(Sum[x]-Sum[l-1])*(Sum[r]-Sum[x])+(Sum[y]-Sum[x])*(Sum[r]-Sum[y])
我们设先切割y的贡献为:
	S_y=(Sum[y]-Sum[l-1])*(Sum[r]-Sum[y])+(Sum[x]-Sum[l-1])*(Sum[y-1]-Sum[x])
设A=Sum[x],B=Sum[y],C=Sum[l-1],D=Sum[r],E=Sum[y-1]
S_x=(A-C)*(D-A)+(B-A)*(D-B)
S_y=(B-C)*(D-B)+(A-C)*(E-A)

S_x-S_y=(A-C)*(D-E)+(D-B)*(C-A)
S_x-S_y=(A-C)*(B-E)
S_x-S_y=(sum[x]-sum[l-1])*(sum[y]-sum[y-1])

显然式子比0大，也就是说顺序下来答案不会变小。