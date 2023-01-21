# Autor: Jefimija Stamenovic 81/2019
# Datum: 20.01.2023. 
############################ ML - PRVE VEZBE ##########################
import pandas as pd 

""" 
Dve osnovne komponente pandas biblioteke su serije i data frame-ovi. 
Serija je kolona, a data frame multidimenzionalna tabela koja predstavlja 
kolekciju serija.

"""
# kreiranje DF od recnika
data = {
    'apples': [3, 2, 0, 1], 
    'oranges': [0, 3, 7, 2]
}
purchases = pd.DataFrame(data)
purchases

# ako zelimo da dodelimo nazive redovima, potrebno je da 
# argumentu index prosledimo listu sa nazivima  
purchases = pd.DataFrame(data, index=['June', 'Robert', 'Lilly', 'David'])
purchases

# uzimanje reda na osnovu njegovog naziva 
june = purchases.loc['June']
june

# preuzimanje podataka iz CSV-a
df = pd.read_csv('purchases.csv')
df

# prilikom ucitavanja csv-a, prva kolona je zapravo kolona sa nazivima indeksa,
# a ne klasicna kolona. Da bismo nazivima indeksa dodelili njene vrednost, 
# potrebno je da setujemo parametar index_col = 0
df = pd.read_csv('purchases.csv', index_col=0)
df

# ucitavanje podataka iz JSON-a
# kod ucitavanja JSON-a, ne moramo da vodimo racuna o nazivima indeksa, 
# prva kolona ce da se gleda kao kolona sa nazivima indeksa
df = pd.read_json('purchases.json')
df

# konvetovanje DF-a u CSV, JSON
df.to_csv('new_purchases.csv')
df.to_json('new_json.csv')

movies = pd.read_csv('IMDB-Movie-Data.csv', index_col='Title')
movies

# zaglavlje DF-a mozemo da vidimo preko funkcije head(). Bez prosledjenog 
# broja u pozivu funkcije, vraca prvih 5 redova, a ukoliko se prosledi broj n 
# vratice n redova 
movies.head()

# zacelje DF-a mozemo da vidimo preko funkcije tail(). Funkcionise isto kao 
# i funkcija tail()
movies.tail()

# funkcija info() obezbedjuje prikaz najbitnijih informacija o dataset-u
# (broj ne null vredosti po kolonama, tip kolone, broj kolona i redova)
movies.info()

# shape vraca broj redova i kolona
rows, columns = movies.shape
rows, columns

# append ce da doda na trenutni DF prosledjeni DF koji moramo da sacuvamo 
# u nekoj promenljivoj 
temp_df = movies.append(movies)
temp_df.shape

temp_df = temp_df.drop_duplicates()
temp_df.shape

# Funkcija drop_duplicates() ima argument keep koji moze da ima tri 
# potencijalne vrednosti: 
# 1. first - ovo je default vrednost koja se prosledjuje ukoliko se 
# keep argument ne prosledjuje pozivu funkcije i on znaci da se brisu 
# svi duplikati sem prvog pojavljivanja 
# 2. last - brisu se svi duplikati sem poslednjeg pojavljivanja 
# 3. false - brisu se svi duplikati (u DF-u ostaju samo jedinstvene vrednosti 
# koje nisu imale nijedan duplikat)
# inplace je argument cija je vrednost true/false i on postoji u okviru svih 
# DF-a. Ukoliko je njegova vrednost na true, onda se poziv trenutno pozvane 
# funkcije izvrsava direktno nad datasetom, a ne pravi se njegova kopija. 
temp_df = movies.append(movies)
temp_df.drop_duplicates(inplace=True, keep='last')
temp_df.shape

# pregled naziva kolona i njihova izmena 
movies.columns
movies.rename(columns= {'Runtime (Minutes)':'Runtime', 'Revenue (Millions)': 'Revenue_millions'}, inplace=True)
movies.columns

movies.columns = [col.lower() for col in movies]
movies.columns

# Postoje dve opcije za rad sa null vrednostima: 
# 1. ukloniti ih 
# 2. popuniti ih nekom vrednoscu (imputacija)

# za svaki podatak u tabeli vraca vrednost true/false u zavisnosti od toga da li je null
movies.isnull()

# kombinacija funkcija isnull i sum ce za svaku kolonu vratiti broj null vrednosti u toj koloni 
movies.isnull().sum()

# funkcija dropna brise svaki red gde se pojavljuje bar jedna null vrednost
movies.dropna()
movies

# axis = 1 znaci da se funkcija izvrsava nad kolonama, odnosno 
# u ovom slucaju, obrisace se 
movies.dropna(axis=1)

# imputacija je metoada koja se koristi za cuvanje vrednih podataka
# koji imaju null vrednosti. Postoje slucajevi kada ima previse redova sa 
# null vrednostima i njihovo uklanjanje u tom slucaju dovodi do gubljenja velikog 
# broja podataka 
# za imputaciju se obicno koristi medijana ili srednja vrednost
revenue = movies['revenue_millions']
revenue
revenue_mean = revenue.mean()
revenue_mean
# popunjavanje null vrednosti 
revenue.fillna(revenue_mean, inplace=True)
revenue

# Funkcija describe() nam daje kratak rezime distribucije 
# kontinualnih promenljivih (count, mean, std, min, kvartili, max)
movies.describe()

# Ova funkcija moze da bude primenjena i na kategorijske promenljive 
# Tada describe() vraca count, broj jedinstvenih, top(najvise zastupljena
# vrednost), freq(count), type 
movies.genre.describe()

# funkcija value_counts nam pokazuje frekvenciju svih podataka u koloni 
movies.genre.value_counts()

# korelaciona matrica 
movies.corr()

# dobijanje serije
genre = movies['genre']
type(genre)

# dobijanje DF-a
genre = movies[['genre']]
type(genre)

subset = movies[['genre', 'rating']]
subset

# izdvanjanje redova po nazivu indeksa 
prometheus = movies.loc['Prometheus']
prometheus

# izdvajanje redova po broju indeksa 
prometheus = movies.iloc[1]
prometheus

# izdvajanje dela DF-a
subset = movies.iloc[1:4]
subset

# ukljucuje Sing u rezultat, dok iloc ne ukljucuje Suicide Squad(4)
subset = movies.loc['Prometheus':'Sing'] 
subset

# selekcija po uslovu 

condition = (movies['director'] == 'Ridley Scott')
condition

movies[movies['director'] == 'Ridley Scott']
movies[movies['rating']>=8.6].head(3)
movies[(movies['director'] == 'Ridley Scott') | (movies['director'] == 'Christopher Nolan')].head(3)
movies[movies['director'].isin(['Christopher Nolan', 'Ridley Scott'])].head(3)
movies[(movies['year']>=2005) & (movies['year'] <= 2010) & (movies['rating']>8.0) & (movies['revenue_millions']< movies['revenue_millions'].quantile(0.25))]

def rating_func(x): 
    if x >= 8.0: 
        return "good"
    else: 
        return "bad"

movies['rating_category'] = movies['rating'].apply(rating_func)
movies

import matplotlib.pyplot as plt
movies.plot(kind='scatter', x = 'rating', y='revenue_millions', title ='Revenue cs Rating')
plt.show()
movies['rating'].plot(kind='box')
plt.show()
movies.boxplot(column='revenue_millions', by='rating_category')
plt.show()

###################################################################################
############################# ML - DRUGE VEZBE ##########################

"""
    Klasifikacioni modeli resavaju pripadnost odredjenoj klasi. Za ocenu 
    kvaliteta modela se koriste metrike: confusion matrix, accuracy, precision, 
    recall(sensitivity), specificity, f1, roc, auc

    Konfuziona matrica je tabela od dve dimenzija - actual i predicted.
    Sastoji se od True Positive (TP), True Negative (TN), 
    False Positive (FP), False Negative (FN) 
"""
import pandas as pd
import seaborn as sns
from sklearn.metrics import confusion_matrix

df = pd.read_csv('data.csv')
df.head()
sns.histplot(df[['model_LR']])
plt.show()

# postavljamo granicu 
thresh = 0.5 
df['predicted_RF'] = (df['model_RF']>thresh).astype(int)
df['predicted_LR'] = (df['model_LR']>thresh).astype(int)

# konfuzionoj matrici prosledjujemo actual i predicted 
cm = confusion_matrix(df['actual_label'], df['predicted_RF'])
cm

# accuracy (tacnost) = (TP + TN)/(TP + FP + FN + TN)
from sklearn.metrics import accuracy_score
accuracy = accuracy_score(df['actual_label'], df['predicted_RF'])
accuracy*100

# precision (preciznost)
from sklearn.metrics import precision_score
precision = precision_score(df['actual_label'], df['predicted_RF'])
precision*100

#recall(sensitivity)
from sklearn.metrics import recall_score
recall = recall_score(df['actual_label'], df['predicted_RF'])
recall*100

# specificity = tn/(tn+fp)
tn, fp, fn, tp = confusion_matrix(df['actual_label'], df['predicted_RF']).ravel()
specificity = tn/(tn+fp)
specificity*100

from sklearn.metrics import f1_score
f1 = f1_score(df['actual_label'], df['predicted_RF'])
f1*100

# roc_auc_score 
from sklearn.metrics import roc_auc_score, roc_curve
fpr, tpr, _ = roc_curve(df['actual_label'], df['model_RF'])
roc_auc_rf = roc_auc_score(df['actual_label'], df['model_RF'])
plt.figure()
plt.plot(fpr, tpr, color = "darkorange", label = "ROC curve RF (area = %0.2f)" % roc_auc_rf)
plt.plot(fpr_lr, tpr_lr, color = "green", label = "ROC curve LR (area = %0.2f)" % roc_auc_lr)
plt.plot([0, 1], [0, 1], color = "navy", lw = 2, linestyle = "--")
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.0])
plt.xlabel("False Positeve Rate")
plt.ylabel("True Positice Rate")
plt.legend(loc = 'lower right')
plt.title("ROC example")
plt.show()

# precision_recall_score 
from sklearn.metrics import precision_recall_curve, auc

precision, recall, thresholds = precision_recall_curve(df['actual_label'], df['model_RF'])
pr_auc = auc(recall, precision)

plt.plot(recall, precision, color = "darkorange", label = "area = %0.2f" % pr_auc)

plt.xlim([0.0, 1.0])
plt.ylim([0.5, 1.0])
plt.xlabel("Recall")
plt.ylabel("Precision")
plt.legend(loc = 'upper right')
plt.title("PRC")
plt.show()

# classification_report 
from sklearn.metrics import classification_report
print(classification_report(df['actual_label'], df['predicted_RF'] ))

################################ III DEO - ML ################################
# Enkoderi sluze da kategorijske promenljive kodiramo na neki nacin 
# ordinal - string labele se konvertuju u vrednosti od 1 do k 
# onehot - jedna kolona za svaku vrednost koja se poredi vs sve druge vrednosti 
# binary - svaka integer vrednost se konertuje u string (8-1000, 7 - 0111)

import pandas as pd
import numpy as np
import copy 
# ucitavamo fajl 
flights = pd.read_csv('https://raw.githubusercontent.com/ismayc/pnwflights14/master/data/flights.csv')
# gledamo osnovne informacije da bismo utvrdili tipove kolona 
# kolone tipa object su potencijalno kategorijske promenljive 
flights.info()

# selektujemo kolone gde je tip podataka object i kopiramo u novi DF
flights_cat = flights.select_dtypes(include=['object']).copy()
flights_cat

# prvo da vidimo null vrednosti po kolonama 
flights_cat.isnull().sum()
# isnull vraca DF sa vrednostima true/false, values ga pretvara u ND niz, a 
# primenom sum() funkcije nad nizom, dobijamo ukupan broj null vrednosti (248)
flights_cat.isnull().values.sum()

# vraca listu count-a za svaku kategoriju unutar ove klase 
list = flights_cat['tailnum'].value_counts()
list
flights_cat = flights_cat.fillna(list[0])
flights_cat.isnull().values.sum()


flights_cat['carrier'].value_counts()

# pretvaranje object klase u kategoriju 
flights_cat = flights.copy()
flights_cat['carrier'] = flights_cat['carrier'].astype('category')
flights_cat['origin'] = flights_cat['origin'].astype('category')

# rad sa kategorijama - codes su vrednosti od 1 do n kategorija
flights_cat['carrier'] = flights_cat['carrier'].cat.codes
flights_cat['carrier']

def us_func(code): 
    if code == 'US': 
        return 1 
    return 0
flights_cat['US_code'] = flights['carrier'].apply(us_func)
flights_cat['US_code']

# Label Encoding 
from sklearn.preprocessing import LabelEncoder
flights_lb = flights.copy()
encoder = LabelEncoder()
flights_lb['carrier_code'] = encoder.fit_transform(flights_lb['carrier'])
flights_lb.head()

# One hot encoding - I nacin 
flights_onehot = flights.copy()
flights_onehot = pd.get_dummies(flights_onehot, columns=['carrier'], prefix=['carrier'])
flights_onehot.head()
flights_onehot.shape

# One hot encoding - II nacin (Label Binarizer)
# iz nekog razloga su nazivi kolona 0..n-1
from sklearn.preprocessing import LabelBinarizer
one_hot = flights.copy()
encoder = LabelBinarizer()
lb_results = encoder.fit_transform(one_hot['carrier'])
lb_df_results = pd.DataFrame(lb_results)
lb_df_results.head()

result_df = pd.concat([one_hot, results_df], axis=1)
result_df

# binary encoding 
import category_encoders as ce 
flights_be = flights_cat.copy()
encoder = ce.BinaryEncoder(cols=['carrier'])
df_binary = encoder.fit_transform(flights_be)
df_binary.head()

#BackwardDifferenceEncoder 
flights_be = flights_cat.copy()
encoder = ce.BackwardDifferenceEncoder(cols=['carrier'])
df_bd = encoder.fit_transform(flights_be)
df_bd.head()

# primer 
dummy_df_age = pd.DataFrame({'age': ['0-20', '20-40', '40-60','60-80']})
def split_mean(x): 
    split_list = x.split('-')
    mean = (float(split_list[0]) + float(split_list[1]))/2
    return mean
dummy_df_age['mean'] = dummy_df_age['age'].apply(split_mean)
dummy_df_age.head()

# linearna regresija 
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn import metrics

dataset = pd.read_csv('Weather.csv')
dataset.head()
dataset.describe()

# prvo radimo reshape
X = dataset['MinTemp'].values.reshape(-1,1)
Y = dataset['MaxTemp'].values.reshape(-1,1)
X.shape

# podela skupa na trening i test
x_train, x_test, y_train, y_test = train_test_split(X, Y, test_size=0.2, random_state=0, shuffle=True)
# podaci su spremni za treniranje 
regressor = LinearRegression()
regressor.fit(x_train, y_train)
regressor.intercept_
regressor.coef_ # koef je oko 92% 

#
y_predicted = regressor.predict(x_test)
df = pd.DataFrame({'Actual':y_test.flatten(), 'Predicted': y_predicted.flatten()})
df.head()

# MAE - srednja apsolutna greska 
metrics.mean_absolute_error(y_test, y_predicted)
# MSE - srednja kvadratna greska 
metrics.mean_squared_error(y_test, y_predicted)
# RMSE - koren srednje kvadratna greska
np.sqrt(metrics.mean_squared_error(y_test, y_predicted))

# visestruka linearna regresija 
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn import metrics

# proveravamo kakav je skup podataka sa kojim radimo 
dataset = pd.read_csv('winequality.csv')
dataset.shape
dataset.describe()

# proveravamo da li i koje kolone imaju null vrednosti 
# funkcija any() ce da vrati true ili false u odnosu na to da li 
# kolona ima null vrednosti (prvo se primenjuje fja isnull)
dataset.isnull().any()

# brisanje null vrednosti - ova linija se nece izvrsiti, posto je 
# rezultat prethodne funkcije pregled svih kolona gde vidimo da nijedna 
# kolona ne sadrzi null vrednosti 
dataset = dataset.fillna(method='ffill')

# na osnovu skupa X cemo da predvidjamo vrednosti za Y 
X = dataset[['fixed acidity', 'volatile acidity', 'citric acid', 'residual sugar', 'chlorides', 'free sulfur dioxide', 'total sulfur dioxide', 'density', 'pH', 'sulphates','alcohol']].values
y = dataset[['quality']].values

# podela podataka na train i test
x_train, x_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=0)

# kreiranje regressora 
regressor =  LinearRegression()
regressor.fit(x_train, y_train)

y_predicted = regressor.predict(x_test)
df = pd.DataFrame({'Actual': y_test.flatten(), 'Predicted':y_predicted.flatten()})
df.head(10)
y_pred_label = [int(x) for x in  np.round(y_pred.flatten()) ]
metrics.accuracy_score(y_test, y_pred_label)

# logistic regression?

##################### ML - IV termin ############################
# KNN - K nearest neighbours algorithm
"""
    1. Ucitati podatke 
    2. Inicijalizovati k najblizih suseda 
    3. Za svaki primer u podacima 
        - izracunati distancu izmedju primera za kog pitamo i trenutnog 
          primera 
        - dodati distancu i indeks u listu 
    4. sortirati listu 
    5. uzeti prvih k elemenata iz liste 
    6. uzeti njihove labele 
    7. ako je regresija, vratiti mean, a ako je klasifikacija, vratiti mode 
"""
import numpy as np 
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score

headernames = ['sepal-length', 'sepal-width', 'petal-length', 'petal-width', 'Class']
path = "https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data"
dataset = pd.read_csv(path)
dataset.head()
x = dataset.iloc[:, :-1].values
y = dataset.iloc[:, 4].values
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.4)


scaler = StandardScaler()
scaler.fit(x_train)
x_train = scaler.transform(x_train)
x_test = scaler.transform(x_test)
classifier = KNeighborsClassifier(n_neighbors=7)
classifier.fit(x_train, y_train)
y_predicted = classifier.predict(x_test)

cm = confusion_matrix(y_test, y_predicted)
cm
classification_report(y_test, y_predicted)

# ANN 
import pandas as pd 
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import confusion_matrix

names = ['sepal-length', 'sepal-width', 'petal-length', 'petal-width', 'Class']
irisdata = pd.read_csv('iris.data', names=names)
irisdata
X = irisdata.iloc[:, 0:4]
y = irisdata.select_dtypes(include=[object])
X.head()
y.head()

# broj jedinstvenih vrednosti u y seriji 
y.Class.unique()
le = preprocessing.LabelEncoder()
y = y.apply(le.fit_transform)

x_train, x_test, y_train, y_test = train_test_split(X, y, test_size=0.2)
scaler = StandardScaler()
scaler.fit(x_train)
x_train = scaler.transform(x_train)
x_test = scaler.transform(x_test)

# kreiranje NN 
mlp = MLPClassifier(hidden_layer_sizes=(10, 10, 10), max_iter=1000)
mlp.fit(x_train, y_train.values.ravel())
predictions = mlp.predict(x_test)
predictions

print(confusion_matrix(y_test,predictions))
print(classification_report(y_test,predictions))