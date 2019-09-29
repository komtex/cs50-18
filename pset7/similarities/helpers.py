from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    list_a = a.split("\n")
    list_b = b.split("\n")
    
    return list_compare(list_a, list_b) 


def sentences(a, b):
    """Return sentences in both a and b"""
    list_a = sent_tokenize(a)
    list_b = sent_tokenize(b)
    
    return list_compare(list_a, list_b)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    list_a = substring_tokenize(a, n)
    list_b = substring_tokenize(b, n)
    
    return list_compare(list_a, list_b)
    
    
def substring_tokenize(a, n):
    """return a list of substrings of size n"""
    output = []
    
    temp = len(a) - n + 1
    for i in range(temp):
        output.append(a[i:n + i])
        
    return output
    
    
def list_compare(a, b):
    """Compare two lists and return the common list of items"""
    output = []
    for i in a:
        for j in b:
            if i == j and j not in output:
                output.append(j)
                
    return output            