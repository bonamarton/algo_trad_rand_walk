import pandas as pd
import numpy as np
from pandas_datareader import data as web
import matplotlib.pyplot as plt
%matplotlib inline

def get_stock(stock,start,end): #define function for querying daily close
 return web.DataReader(stock,'google',start,end)['Close']

def RSI(series, period): #define function for RSI
 delta = series.diff().dropna()
 u = delta * 0
 d = u.copy()
 u[delta > 0] = delta[delta > 0]
 d[delta < 0] = -delta[delta < 0]
 u[u.index[period-1]] = np.mean( u[:period] ) #first value is sum of avg gains
 u = u.drop(u.index[:(period-1)])
 d[d.index[period-1]] = np.mean( d[:period] ) #first value is sum of avg losses
 d = d.drop(d.index[:(period-1)])
 rs = pd.stats.moments.ewma(u, com=period-1, adjust=False) / \
 pd.stats.moments.ewma(d, com=period-1, adjust=False)
 return 100 - 100 / (1 + rs)
 #function creates two series of daily differences
 #one series is daily positive differences, i.e. gains
 #one series is daily negative difference, i.e. losses.
 #average daily positive differences for the period specified.
 #average daily negative difference for the period specified.
 #RS is set equal to Exponential Moving Average of daily positive differences for the period sepcified / Exponential Moving Average of daily positive differences for the period sepcified.
 #return 100 – 100 / (1 + RS)

#DataFrame
#df = pd.DataFrame(get_stock()
df = pd.DataFrame(get_stock('FB', '1/1/2018', '05/31/2018')) #query daily close for ‘FB’ during 2018.


df['RSI'] = RSI(df['Close'], 14) #run daily close through RSI function. Save series to new column in dataframe
df.tail()

df.plot(y=['Close']) #plot daily close and RSI
df.plot(y=['RSI'])

