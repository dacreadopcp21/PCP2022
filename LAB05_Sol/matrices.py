# Operatoria con Matrices
# Recuperado de https://bit.ly/3LZkV1q

A = [[1,-1,1],[2,2,3],[-2,-3,-1]]
B = [[1,0,4],[0,2,5],[1,3,0]]

prodc = [[0 for x in range(3)] for y in range(3)]  
  
for i in range(len(A)): 
    for j in range(len(B[0])): 
        for k in range(len(B)): 
            prodc[i][j] += A[i][k] * B[k][j] 
  
print(prodc)
