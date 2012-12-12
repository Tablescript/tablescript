// staffs.ts
//

table _staffs {
	1:		("Staff of size alteration")
	2:		("Staff of charming")
	3:		("Staff of healing")
	4:		("Staff of fire")
	5:		("Staff of swarming insects")
	6:		("Staff of frost")
	7:		("Staff of earth and stone")
	8:		("Staff of defense")
	9:		("Staff of woodlands")
	10:		("Staff of life")
	11:		("Staff of passage")
	12:		("Staff of power")
}

table staffs_medium d100 {
	1-10:	(_staffs[1])
	11-20:	(_staffs[2])
	21-30:	(_staffs[3])
	31-40:	(_staffs[4])
	41-50:	(_staffs[5])
	51-60:	(_staffs[6])
	61-70:	(_staffs[7])
	71-80:	(_staffs[8])
	81-89:	(_staffs[9])
	90-95:	(_staffs[10])
	96-100:	(_staffs[11])
}

table staffs_major d100 {
	1-5:	(_staffs[2])
	6-15:	(_staffs[3])
	16-30:	(_staffs[4])
	31-40:	(_staffs[5])
	41-50:	(_staffs[6])
	51-60:	(_staffs[7])
	61-70:	(_staffs[8])
	71-80:	(_staffs[9])
	81-90:	(_staffs[10])
	91-96:	(_staffs[11])
	97-100:	(_staffs[12])
}

for i in range(10) {
	if(d2 == 1) {
		print(staffs_medium());
	} else {
		print(staffs_major());
	}
}
