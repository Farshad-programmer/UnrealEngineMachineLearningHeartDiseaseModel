import os
import pandas as pd
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split



def CreateModel():
    np.random.seed(42)
    heart_disease = pd.read_csv("C:/UnrealProjects/CPY/Source/CPY/heart-disease.csv")
    X = heart_disease.drop("target", axis=1)
    Y = heart_disease["target"]

    x_train, x_test, y_train, y_test = train_test_split(X, Y, test_size=0.2)

    clf = RandomForestClassifier()
    clf.fit(x_train, y_train)

    score = clf.score(x_test, y_test)
    print(f"Model accuracy : {score: .2}")

    final_Score = score * 100
    print(f"Model accuracy : {final_Score:.2f}%")

    input_file_path = 'C:/UnrealProjects/CPY/Source/CPY/fromC++.txt'
    output_file_path_result = r'C:\UnrealProjects\CPY\Source\CPY\frompython.txt'
    output_file_path_modelAccuracy = r'C:\UnrealProjects\CPY\Source\CPY\modelaccuracy.txt'

    # Define a new patient data
    new_patient = pd.read_csv(input_file_path)
    
    # Predict using the trained model
    prediction = clf.predict(new_patient)
    print(f"Prediction for our new patient: {'Positive' if prediction[0] == 1 else 'Negative'}")
    if prediction[0] == 1:
        result = 'Positive'
    else:
        result = 'Negative'


    # Prepare the output message
    output_message = f"Prediction for our new patient: {result}"
    output_message2 = f"Model accuracy : {final_Score:.2f}%"

    # Save the output1 to a new file
    with open(output_file_path_result, 'w') as file:
        file.write(output_message)

    # Save the output2 to a new file
    with open(output_file_path_modelAccuracy, 'w') as file:
        file.write(output_message2)


# Execute the function when the script runs
if __name__ == "__main__":
    CreateModel()
    




