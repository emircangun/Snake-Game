import os

class Config():
    DEBUG = False
    TESTING = False
    DATABASE_URI = os.environ.get("MONGODB_URI")    

class DevelopmentConfig(Config):
    DEBUG = True

class TestingConfig(Config):
    TESTING = True

class ProductionConfig(Config):
    pass
