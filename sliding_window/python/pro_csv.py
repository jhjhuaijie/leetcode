import csv
users = ["a", "d", "g"]
def parse_csv():
    with open("1.csv", "rb") as reader_csv :
        with open("out.csv", "wb") as writer_csv :
            reader = csv.reader(reader_csv)
            writer = csv.writer(writer_csv)
            header = next(reader)
            writer.writerow(header)

            for row in reader :
                name = row[0]
                user = name.split("/")[-1]
                if user in users :
                    row[1] = "ok"
                writer.writerow(row)
        writer_csv.close()
    reader_csv.close()

if __name__ == "__main__" :
    parse_csv()