import hashlib
import sqlite3
import random
import time

class Hash:

    """
    Hesiranje SHA256 algoritmom
    """
    def hash(password:str):
        newPassword=password.encode("utf-8")
        hash_object=hashlib.sha256()
        hash_object.update(newPassword)
        return hash_object.hexdigest()
    
    """
    Uporedjivanje plain i hesirane lozinke
    """
    def compare(password:str,hashedPassword:str):
        cryptedPassword=Hash.hash(password)
        return cryptedPassword==hashedPassword
    
def dict_factory(cursor, row):
    d = {}
    for idx, col in enumerate(cursor.description):
        d[col[0]] = row[idx]
    return d

def redirect_to_page(page):
    ROOT_URL_PAGES="http://localhost:8000/cgi-bin/pages"
    print("Content-Type:text/html\n\n")
    print()
    print(f"<script>window.location='{ROOT_URL_PAGES}/{page}.py'</script>")

class SingletonConnection:
    _instance=None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.__initialize()
        return cls._instance

    def __initialize(self):
        self.connection=sqlite3.connect('seminarski.db')
        self.connection.row_factory=dict_factory

class Session:
    def __get_random_string(length=12,allowed_chars='abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'):
        random.seed(
            hashlib.sha256(
                ("%s%s%s" % (
                    random.getstate(),
                    time.time(),
                    '63c1dd951ffedf6f7fd968ad4efa39b8ed584f162f46e715114ee184f8de9201')).encode('utf-8')
            ).digest())
        return ''.join(random.choice(allowed_chars) for i in range(length))

    def __init__(self,cookie) -> None:
        self.connection=SingletonConnection().connection
        if ( ("SESSION_ID" in cookie) and (cookie['SESSION_ID'].value!="None")):
            self.session_id=cookie['SESSION_ID'].value
        else:
            self.session_id=Session.__get_random_string()
            cookie['SESSION_ID']=self.session_id
            cookie['SESSION_ID']['path']="/"

    def __getitem__(self,key):
        cursor=self.connection.execute("""
        SELECT value 
        FROM sessions 
        WHERE SESSION_ID=? AND key=? 
        """,(self.session_id,key))
        a=cursor.fetchone()
        cursor.close()
        if(a is None):
            return None
        return a['value']
    
    def __setitem__(self,key,value):
        if value is not None:
            self.connection.execute("""
            REPLACE INTO sessions 
            VALUES(?,?,?)
            """,(self.session_id,key,value))
        else:
            self.connection.execute("""
            DELETE FROM sessions
            WHERE SESSION_ID=? AND key=?
            """,(self.session_id,key))
        self.connection.commit()
    
    def __delitem__(self,key):
        self.connection.execute("""
        DELETE FROM sessions 
        WHERE SESSION_ID=? AND key=? 
        """,(self.session_id,key))
        self.connection.commit()

    def destroy(self):
        self.connection.execute("""
        DELETE FROM sessions 
        WHERE SESSION_ID=?
        """,(self.session_id,))
        self.connection.commit()
    