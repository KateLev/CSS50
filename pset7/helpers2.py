from nltk.tokenize import sent_tokenize  # to use sent_tokenize function in sentences

result_set = set()  # I decided to use set, because we don't need any duplicates and only one NULL line
file1 = set()
file2 = set()

def compare_strings(file1, file2):
    for line in file1:  # compare sentences in files
        for line2 in file2:
            if line == line2:
                result_set.add(line)

def split_string_n (file, s, n):
    n = int(n)
    i = 0
    while (i + n) <= len(s):
        file.add(s [i:i + n])
        i = i + 1
    return file


def lines(a, b):
    """Return lines in both a and b"""

    file1 = a.splitlines()  # we need to split strings into lines
    file2 = b.splitlines()

    compare_strings(file1, file2)
    return result_set


def sentences(a, b):
    """Return sentences in both a and b"""

    file1 = sent_tokenize(a, language='english')
    file2 = sent_tokenize(b, language='english')

    compare_strings(file1, file2)
    return result_set



def substrings(a, b, n):
    """Return substrings of length n in both a and b"""


    split_string_n(file1, a, n)
    split_string_n(file2, b, n)

    compare_strings(file1, file2)
    return result_set
