#This program is only a little part of a bigger project (still not public) --- Clearly is not finished :)

import csv
import requests
from bs4 import BeautifulSoup

#Functions

def main():
    titles = base_scraper("https://pypi.org/project/beautifulsoup4/","h1")
    #paragraphs = base_scraper("https://pypi.org/project/beautifulsoup4/","p")
    dataset_creator(titles)
    #dataset_creator(paragraphs)


# Receive a website URL and an HTML tag to look for and return the list with the desired informations
def base_scraper(URL, HTML_TAG_condition):
    SERVER_response = requests.get(URL) #HTML code response received from the server (es. 200, 404, 301 etc.)
    HTML_content = SERVER_response.content #HTML webpage content (HTML tags, paragraph etc.)
    soup = BeautifulSoup(HTML_content, 'html.parser')

    return soup.find_all(HTML_TAG_condition)


# Receive a dirty list. Cleans it and write it into a consistent csv dataset 
def dataset_creator(list):
    print(list)
    #fetch and catalog the list received and fix the CSV syntax so that it's possible to correctly upload it into a csv dataset


#Main execution code
if __name__ == "__main__":
    main()
