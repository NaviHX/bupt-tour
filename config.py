f = open("config-pre","r")
out = open("config","w")
lines=f.readlines()
lines[0]=lines[0].split(" ")
lines[1]=lines[1].split(" ")
total=int(lines[0][0])
road=int(lines[0][1])
broad=int(lines[0][2])
v=int(lines[1][0])
bv=int(lines[1][1])
tt=int(lines[2])
out.write("{0} {1} {2}\n{3} {4}\n{5}\n".format(total,road,broad,v,bv,tt))

dic={}
i=3
offset=0
while i<3+total+offset:
    if lines[i][0]=="#":
        offset += 1
        i += 1
        continue
    out.write(lines[i])
    lines[i]=lines[i].split(" ")
    dic[lines[i][0]]=i-3-offset
    i += 1

i=3+total+offset
st=i
offset=0
while i<st+road+offset:
    if lines[i][0]=="#":
        offset += 1
        i += 1
        continue
    lines[i]=lines[i].split(" ")
    lines[i][0]=dic[lines[i][0]]
    lines[i][1]=dic[lines[i][1]]
    out.write("{0} {1} {2} {3} {4}".format(lines[i][0],lines[i][1],lines[i][2],lines[i][3],lines[i][4]))
    i += 1

st=i
offset=0
while i<st+broad+offset:
    if lines[i][0]=="#":
        offset += 1
        i += 1
        continue
    lines[i]=lines[i].split(" ")
    lines[i][0]=dic[lines[i][0]]
    lines[i][1]=dic[lines[i][1]]
    out.write("{0} {1} {2} {3} {4}".format(lines[i][0],lines[i][1],lines[i][2],lines[i][3],lines[i][4]))
    i += 1
