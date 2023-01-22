import numpy as np
import pandas as pd
import seaborn as sns
# Учитати сет податка diamonds.csv
data = pd.read_csv('diamonds.csv')
df = data.copy()

# Проверити да ли неке вредности података недостају. 
# Уколико недостаје део података,попунити просечним 
# вредностима за тај тип података
df.isnull().sum()

# Чистоћу дијаманта кодирати методом Label Encoding, 
# а преостале категоријске варијабле
# кодирати методом One-Hot-Encoding
from sklearn.preprocessing import LabelEncoder
encoder = LabelEncoder()
df['clarity'] = encoder.fit_transform(df['clarity'])
df.columns

categories = df.select_dtypes(include=['object']).columns
categories
df = pd.get_dummies(df, columns = categories, prefix=categories)
df.columns

# Поделити податке на скуп за обуку и скуп за тестирање у односу 70:30
from sklearn.model_selection import train_test_split
x = df.loc[:, df.columns != 'price'].values
y = df.loc[:, 'price'].values
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.3, random_state=50, shuffle=True)

""" 
    Креирати и обучити моделе вишеструке линеарне регресије и 
    вештачке неуронске мреже.
    ANN модел садржи 2 скривена слоја са по 5 неурона.
"""
from sklearn.linear_model import LinearRegression
regressor = LinearRegression()
regressor.fit(x_train, y_train)
y_lr_pred = regressor.predict(x_test)

from sklearn.neural_network import MLPRegressor
from sklearn.preprocessing import StandardScaler

scaler = StandardScaler()
scaler.fit(x_train)
x_train = scaler.transform(x_train)
x_test = scaler.transform(x_test)
nn_regressor = MLPRegressor(hidden_layer_sizes=(5,5), max_iter=50)
nn_regressor.fit(x_train, y_train.ravel())
y_nn_pred = nn_regressor.predict(x_test)

# Извршити предикције на тестном скупу.
df_lin = pd.DataFrame({'Actual': y_test, 'Predicted': y_lr_pred})
df_lin.head()

df_nn = pd.DataFrame({'Actual': y_test, 'Predicted': y_nn_pred})
df_nn.head()

# Потом одредити метрике оба модела на тестном скупу MAE i RMSE 
from sklearn.metrics import mean_absolute_error, mean_squared_error
mae_lr = mean_absolute_error(y_test, y_lr_pred)
rmse_lr = np.sqrt(mean_squared_error(y_test, y_lr_pred))
print("MAE LR : ", mae_lr)
print("RMSE LR : ", rmse_lr)

mae_nn = mean_absolute_error(y_test, y_nn_pred)
rmse_nn = np.sqrt(mean_squared_error(y_test, y_nn_pred))
print("MAE NN : ", mae_nn)
print("RMSE NN : ", rmse_nn)

"""
За модел са мањом грешком МАЕ нацртати дијаграм распршености. 
На 𝑥 оси налазе се стварне вредности, а на 𝑦 оси налазе се придиковане 
вредности. Исцртати праву 𝑦 = 𝑥 наистом графику.
"""
import matplotlib.pyplot as plt
plt.scatter(y_test, y_nn_pred,  color='gray')
plt.plot(y_test, y_test, color='red', linewidth=2)
plt.show()