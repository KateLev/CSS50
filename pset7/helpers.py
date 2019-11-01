from nltk.tokenize import sent_tokenize  # to use sent_tokenize function in sentences

def lines(a, b):
    """Return lines in both a and b"""

    file1 = set()
    file2 = set()
    result_set = set()  # I decided to use set, because we don't need any duplicates and only one NULL line
    file1 = a.splitlines()  # we need to split strings into lines
    file2 = b.splitlines()
    #  print (file1)
    #  print (file2)
    for line in file1:  # compare strings in files
        for line2 in file2:
            if line== line2:
                result_set.add(line)
    #  print("Result = ", result_set)
    return result_set


def sentences(a, b):
    """Return sentences in both a and b"""

    file1 = set()
    file2 = set()
    result_set = set()  # I decided to use set, because we don't need any duplicates and only one NULL line
    file1 = sent_tokenize(a, language='english')
    file2 = sent_tokenize(b, language='english')
    #  print (file1)
    #  print (file2)
    for line in file1:  # compare sentences in files
        for line2 in file2:
            if line== line2:
                result_set.add(line)
    #  print("Result = ", result_set)
    return result_set



def substrings(a, b, n):
    """Return substrings of length n in both a and b"""


    n = int(n)
#    a = a.strip('\n')
#    b.strip('\n')
    file1 = list()
    file2 = list()
    result_set = set()  # I decided to use set, because we don't need any duplicates and only one NULL line
    i = 0
    while (i + n) <= len(a):
        file1.append(a [i:i + n])
        i = i + 1
#    print (file1)
    i = 0
    while (i + n) <= len(b):
        file2.append(b [i:i + n])
        i = i + 1
    for line in file1:  # compare sentences in files
        for line2 in file2:
            if line== line2:
                result_set.add(line)
    return result_set
