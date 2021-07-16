from flask import Flask
import views
from database import Database

# creating app and getting config from module
app = Flask(__name__)
app.config.from_object("configmodule.DevelopmentConfig")

# creating database and adding to config
db = Database()
app.config["db"] = db

# /api/users/login
# /api/users/signup
app.add_url_rule(
    "/api/users/login", view_func=views.login, methods=["POST"]
)
app.add_url_rule(
    "/api/users/signup", view_func=views.signup, methods=["POST"]
)

# /api/<username>/<game_id>  -> get
# /api/<username>/add_game   -> post
app.add_url_rule(
    "/api/users/<string:username>/<int:game_id>", view_func=views.get_game, methods=["GET"]
)
app.add_url_rule(
    "/api/users/<string:username>/add_game", view_func=views.add_game, methods=["POST"]
)



if __name__ == "__main__":
    app.run()