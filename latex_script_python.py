import csv
import sqlite3
import sys
import json
from pprint import pprint

conn = sqlite3.connect("test.db")
conn.text_factory = str
cur = conn.cursor()
cur.execute("DROP TABLE IF EXISTS new;")
with open('sample.csv') as f:
  reader = csv.reader(f)
  row1 = next(reader)   #gets the first line
print row1
print len(row1)
string = ','.join(row1)
if string[len(string) - 1] != ',' :
    string = string + ','
string = string.replace(',', ' varchar(10),')
temp = list(string)
del temp[len(string) - 1]
string = ''.join(temp)
print string
cur.execute("CREATE TABLE new (%s);" % string)
cur.execute("select * from new;")
one = ''
for i in range(0, len(row1)) :
    one =
with open('sample.csv', 'r') as csvfile :
    dic = csv.DictReader(csvfile)
    print dic
    to_db = [(i['xcord'],i['ycord'],i['a'],i['b']) for i in dic]
    print to_db
no_question_marks = '?,'*len(row1)
no_question_marks = no_question_marks[0:len(no_question_marks) - 1]
print no_question_marks
cur.executemany("INSERT into new values(%s);" % no_question_marks, to_db)
db_new = [str(map(int, i)) for i in to_db]
print to_db
conn.commit()

script = open("a.txt", "w")

sequence = ["\\documentclass{article}\n","\\usepackage[margin=0.5in]{geometry}\n","\\usepackage[utf8]{inputenc}\n","\\usepackage{pgfplots}\n","\\pgfplotsset{width=10cm,compat=1.9}\n","\\begin{document}\n"]
script.writelines(sequence)

#******************************************************************************#
def line_plot() :

    xmin = 0                                                                    #liable to change
    ymin = 0
    xmax = to_db[len(to_db) - 1][0]
    ymax = to_db[len(to_db) - 1][1]
    xtick = (int(xmin) + int(xmax))/len(to_db)
    ytick = (int(ymin) + int(ymax))/len(to_db)
    l1 = [int(xmin),]
    for i in range(1, len(to_db)) :
        s = int(l1[i - 1]) + xtick
        l1.append(s)
    temp = str(l1)
    t = list(temp)
    t[0] = ''
    t[len(t) - 1] = ''
    temp = ''.join(t)
    xtick = ''.join(("{",temp,"}"))
    l2 = [int(ymin),]
    for i in range(1, len(to_db)) :
        s = int(l2[i - 1]) + ytick
        l2.append(s)
    temp = str(l2)
    t = list(temp)
    t[0] = ''
    t[len(t) - 1] = ''
    temp = ''.join(t)
    ytick = ''.join(("{",temp,"}"))
    string = ''.join(db_new)
    new = list(string)
    for i in range(0, len(new)) :
        if new[i] == '[' :
            new[i] = '('
        if new[i] == ']' :
            new[i] = ')'
        if new[i] == ' ' :
            new[i] = ''
    coordinates = ''.join(new)

    script.seek(0, 2)

    coordinates1 = coordinates.replace("(", "")
    coordinates1 = coordinates1.replace(")", " \n")
    coordinates1 = coordinates1.replace(",", " ")

    temp = list(coordinates1)
    del temp[len(temp) - 1]
    coordinates1 = ''.join(temp)
    print coordinates1

    s = ""
    for i in coordinates1.split("\n") :
        color_of_mark = raw_input("Enter the color of the mark : ")
        i = i + color_of_mark
        s = s + i + "\n"

    temp = list(s)
    del temp[len(temp) - 1]
    s = ''.join(temp)

    print s

    nature_of_line = "dotted,"                                                  #user input with comma
    legend_position = "north west"                                              #user input
    grid_style = "dashed"                                                       #user input
    color = "red"                                                               #user input
    mark_style = "square"                                                       #user input
    scale = 2                                                                   #user input

    #with open('data.json') as input_file:
    #    file_data = json.load(input_file);
    #*********json file parsing**********#
    #pprint(file_data)

    string = '''\\begin{tikzpicture}
    \\begin{axis}[
        title={Prototype},
        xlabel={X-axis},
        ylabel={Y-axis},
        xmin=%d, xmax=%d,
        ymin=%d, ymax=%d,
        xtick=%s,
        ytick=%s,
        legend pos=%s,
        ymajorgrids=true,
        grid style=%s,
        ]
    \\addplot[
        %s color=%s, mark=%s, mark options={scale=%d}
        ]
        coordinates {
        %s
        };
        \legend{saurabh}
        \end{axis}
        \end{tikzpicture}''' % (int(xmin), int(xmax), int(ymin), int(ymax), xtick, ytick, legend_position, grid_style, nature_of_line, color, mark_style, scale, coordinates)

    script.write(string)

#******************************************************************************#
def scatter_plot() :

    script.seek(0, 2)

    no_labels = input("No. of labels : ")
    label = {}
    for i in range(0, no_labels) :
      i = raw_input("Name of label : ")
      label[i] = []
      mark = raw_input("Enter the mark : ")
      color = raw_input("Enter the color : ")
      label[i].append("mark=" + mark)
      label[i].append(color)
    output = str(label)
    output = output.replace("[", "")
    output = output.replace("]", "")
    output = output.replace("{", " ")
    output = output.replace("}", "")
    output = output.replace(" ", "")
    output = output.replace("'", "")
    output = output.replace(":", "={")
    temp = list(output)
    count = 0
    check = 0
    for i in temp :
        if i == ',' :
            count = count + 1
        if count % 2 == 0 and count != 0 and i == ',':
            j = i.replace(",", "},")
            temp[check] = j
        check = check + 1
    temp.append('}')
    output = ''.join(temp)
    print output

    string = ''.join(db_new)
    new = list(string)
    for i in range(0, len(new)) :
        if new[i] == '[' :
            new[i] = '('
        if new[i] == ']' :
            new[i] = ')'
        if new[i] == ' ' :
            new[i] = ''
    coordinates = ''.join(new)
    coordinates1 = coordinates.replace("(", "")
    coordinates1 = coordinates1.replace(")", " \n")
    coordinates1 = coordinates1.replace(",", " ")

    temp = list(coordinates1)
    del temp[len(temp) - 1]
    coordinates1 = ''.join(temp)
    print coordinates1

    s = ""
    for i in coordinates1.split("\n") :
        color_of_mark = raw_input("Enter the label : ")
        i = i + color_of_mark
        s = s + i + "\n"

    temp = list(s)
    del temp[len(temp) - 1]
    s = ''.join(temp)

    string = '''
    \\begin{tikzpicture}
	\\begin{axis}[
	clickable coords={(xy): \\thisrow{label}},
	scatter/classes={
	   %s}
    ]
	\\addplot[scatter,only marks,scatter src=explicit symbolic]
	table[meta=label] {
    x     y    label
    %s
	};
	\end{axis}
    \end{tikzpicture}''' % (output, s)

    script.write(string)

#******************************************************************************#
def bar_chart() :

    script.seek(0, 2)

    string = ''.join(db_new)
    new = list(string)
    for i in range(0, len(new)) :
        if new[i] == '[' :
            new[i] = '('
        if new[i] == ']' :
            new[i] = ')'
        if new[i] == ' ' :
            new[i] = ''
    coordinates = ''.join(new)

    y_label = "sqlite"
    space_over_bars = 0.05
    xcord_legend = 0.5
    ycord_legend = -0.1
    anchor_position = "north"
    interval_between_bars = 0.7
    legend_1 = "one"
    legend_2 = "two"

    string = '''
    \\begin{tikzpicture}
    \\begin{axis}[
	x tick label style={/pgf/number format/1000 sep=},
	ylabel=%s,
	enlargelimits = %f,
	legend style={at={(%d,%d)},	anchor=%s, legend columns=-1},
	ybar interval=%f,
    ]
    \\addplot
	coordinates {%s};
    \legend{%s,%s}
    \end{axis}
    \end{tikzpicture}''' % (y_label, space_over_bars, xcord_legend, ycord_legend, anchor_position, interval_between_bars, coordinates, legend_1, legend_2)

    script.write(string)

#******************************************************************************#
#call functions here
#line_plot()

#script.seek(0, 2)
#script.write("\n\hskip 5pt\n")

#scatter_plot()

#script.seek(0, 2)
#script.write("\n\hskip 5pt\n")

bar_chart()

script.seek(0, 2)
script.write("\n\end{document}\n")
