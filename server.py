import os
import pandas as pd
import pickle
#from sklearn.externals import joblib
from flask import Flask, jsonify, request

app = Flask(__name__)


@app.route('/predict', methods=['POST'])
def apicall():
    """API Call

    Pandas dataframe (sent as a payload) from API Call
    """
    try:
        test_json = request.get_json()
        test = pd.read_json(test_json, orient='records')

        loan_ids = test['id_place']

    except Exception as e:
        raise e

    clf = 'model_reccomend.pk'

    if test.empty:
        print('empty_result')
    else:
        # Load the saved model
        print("Loading the model...")
        loaded_model = None
        with open('./' + clf, 'rb') as f:
            loaded_model = pickle.load(f)

        print("The model has been loaded...doing predictions now...")
        predictions = loaded_model.predict(test)

        prediction_series = list(pd.Series(predictions))

        final_predictions = pd.DataFrame(list(zip(loan_ids, prediction_series)))

        responses = jsonify(predictions=final_predictions.to_json(orient="records"))
        responses.status_code = 200

        return (responses)