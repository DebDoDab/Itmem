from __future__ import print_function
import pickle
import os.path
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
import random


def generate_number(goal: int) -> int:
    x = random.random()
    x **= 1.7
    minus = random.randint(0, 1)
    if minus == 0:
        minus = -1
    x *= minus
    return goal + x

def generate_numbers(amount: int, goal: int) -> list:
    x = []
    for i in range(amount):
        x.append(generate_number(goal))
    return x

def refactor_values(values: list) -> list:
    new_values = []
    for value in values:
        new_values.append([value])
    return new_values


def write(values: list) -> None:
    SCOPES = ['https://www.googleapis.com/auth/spreadsheets']
    SPREADSHEET_ID = '1kiHVOjGDyGTdds3n5pTSHHRfI-uBbzLepjn1qmIR-NM'
    RANGE_NAME = 'Sheet1!B2:B201'

    creds = None
    # The file token.pickle stores the user's access and refresh tokens, and is
    # created automatically when the authorization flow completes for the first
    # time.
    if os.path.exists('token.pickle'):
        with open('token.pickle', 'rb') as token:
            creds = pickle.load(token)
    # If there are no (valid) credentials available, let the user log in.
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(
                'credentials.json', SCOPES)
            creds = flow.run_local_server(port=0)
        # Save the credentials for the next run
        with open('token.pickle', 'wb') as token:
            pickle.dump(creds, token)

    service = build('sheets', 'v4', credentials=creds)

    sheet = service.spreadsheets()

    body = {
        'values': values
    }

    result = sheet.values().update(
        spreadsheetId=SPREADSHEET_ID, range=RANGE_NAME,
        valueInputOption='RAW', body=body).execute()

    print('{0} cells updated.'.format(result.get('updatedCells')))



if __name__ == '__main__':
    values = generate_numbers(200, 10)
    values = refactor_values(values)
    write(values)


