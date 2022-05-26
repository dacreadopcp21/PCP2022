import pandas as pd

### df (data frame) -> Var que guarda el archivo .xlsx
 
df = pd.read_excel(io = "pens_universal.xlsx", sheet_name="PGU", header = None, names = ['region',
'cod_comuna','comuna','hombre','monto_hombre','mujer','monto_mujer','total','monto_total'], usecols= ['hombre',
'monto_hombre'])
 
print(df)
#print(df.head())
#print(df.dtypes)
#print(df.columns)
#print(pd.unique())

