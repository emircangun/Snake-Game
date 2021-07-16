'''
    login
    sign_up
    
    get_game
    add_game
'''

#  burada password hash et, api arası hash olmayan password geçişi sağlıklı mıdır?

from werkzeug.security import generate_password_hash, check_password_hash

# existing user
def login():
    '''
        return succeed or failed, error kodları göster
    '''

    pass

# new user
def signup():
    pass


def get_game(username, game_id):
    pass


def add_game(username):
    pass