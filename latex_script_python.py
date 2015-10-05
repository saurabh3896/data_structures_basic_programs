import csv
import sqlite3
import sys

conn = sqlite3.connect("test.db")
conn.text_factory = str
cur = conn.cursor()
cur.execute("DROP TABLE IF EXISTS new;")
cur.execute("CREATE TABLE new (xcord varchar(10), ycord varchar(10));")
with open('sample.csv', 'r') as csvfile :
    dic = csv.DictReader(csvfile)
    to_db = [(i['xcord'],i['ycord']) for i in dic]
cur.executemany("INSERT into new values(?,?);", to_db)
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

#def bar_chart() :


#******************************************************************************#
#call functions here
#line_plot()

#script.seek(0, 2)
#script.write("\n\hskip 5pt\n")

scatter_plot()
#bar_chart()

script.seek(0, 2)
script.write("\n\end{document}\n")
