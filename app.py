from flask import Flask


# creating app and getting config from module
app = Flask(__name__)
app.config.from_object("configmodule.DevelopmentConfig")






if __name__ == "__main__":
    app.run()