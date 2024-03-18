#Importing
import requests
import sys
import os
import wget
import re


#Functions
def main(argv):
    if len(sys.argv) < 2:
        chromeVersion = string(input("Not enough arguments provided. Which chrome version do you need?")).rstrip()
    elif len(sys.argv) == 2:
        chromeVersion = sys.argv[1]
        print(f"Checking Chrome build: {chromeVersion} ...\n")
    else:
        print("Something went wrong... Exiting the program")
        exit()

    chromeReleaseChecker(chromeVersion)


#Check the latest code of the asked build
def chromeReleaseChecker(chromeVersion):
    version_found = []
    count = 0 #not totally usefull this var initializing
    version_chosen = 0 #not totally usefull this var initializing
    urlChromeDriver = "https://googlechromelabs.github.io/chrome-for-testing/known-good-versions-with-downloads.json"
    json_response = requests.get(urlChromeDriver).json()
    pattern = chromeVersion #just for better readability through the while cycle
    
    while True:
        count = 0
        for version in json_response['versions']:
            regex_case = re.search(rf"^{pattern}", version['version']) #regex used for simpler and more effective pattern search
            if regex_case: #if the pattern matches
                count += 1
                version_found.append(version['version']) #appending into the list the new item
                print(f"{count}: {version['version']}") #just printing to the user the item found
                
        user_cond = int(input("\nWhich one do you need? ->  ")) #user_cond is the number of the version list
        user_cond -= 1 #aligning the option chosen by the user to the index of the array
        try:
            version_chosen = version_found[user_cond]
        except:
            print("I think that number was not on the list. Exiting the program.")
            exit()

        confirm_cond = input(f"Do you confirm the version: {version_chosen}? [y/n] -> ") 
        if confirm_cond == "n":
            continue
        elif confirm_cond == "y" or confirm_cond == "":
            break
        else:
            print("Sorry. I didn't understand what you said. Exiting the program")
            exit()

    chromeReleaseDownloader(version_chosen) #calling another function


#Download the asked version
def chromeReleaseDownloader(version_chosen):
    current_path = os.getcwd() #get currernt working dir
    url = f"https://storage.googleapis.com/chrome-for-testing-public/{version_chosen}/win32/chromedriver-win32.zip" #concatenate the version_chosen with the rest of the URL
    try:
        chromeDriverFile = wget.download(url, out=current_path) #try to download what the URL sent
    except:
        print("Something went wrong while downloading the file. Try to paste in your browser the following URL:\n")
        print(url)
        exit()
    print("\n")

    

#Main execution code
if __name__ == "__main__":
    main(sys.argv)
