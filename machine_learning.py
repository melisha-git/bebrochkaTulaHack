import pandas as pd
from sklearn.model_selection import train_test_split, GridSearchCV

from sklearn.metrics import mean_squared_error
from sklearn.linear_model import LinearRegression, LogisticRegression

from sklearn.metrics import r2_score, f1_score

import warnings
warnings.filterwarnings("ignore")

data = pd.read_excel(r'recom_test.xlsx')
test, train = train_test_split(data, test_size=0.2, random_state=12345)
print(test)




