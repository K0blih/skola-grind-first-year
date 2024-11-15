#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    int index;
    char* name;
    float startValue;
    float endValue;
    int tradeCount;
    float sub;
};

void printWithUnderscores(int number);

int main(int argc, char *argv[])
{
    char* t = "0";
    int n = 0;

    if (argc != 3) {
        printf("Wrong parameters\n");
        return 1;
    }
    else {
        t = argv[1];
        n = atoi(argv[2]);
    }

    struct Record* records = (struct Record*)malloc(n * sizeof(struct Record));

    char buffer[101];
    for (int i = 0; i < n; i++) {
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        char *token = strtok(buffer, ",");
        int j = 1;
        while (token) {
            switch (j) {

                case 1:
                records[i].index = atoi(token);
                break;

                case 2:
                records[i].name = (char*)malloc((strlen(token) + 1) * sizeof(char));
                strcpy(records[i].name, token);
                break;

                case 3:
                records[i].startValue = (float)atof(token);
                break;

                case 4:
                records[i].endValue = (float)atof(token);
                break;

                case 5:
                records[i].tradeCount = atoi(token);
                break;
            }
            j++;
            token = strtok(NULL, ",");
        }

        records[i].sub = records[i].endValue - records[i].startValue;
    }

    int existFlag = 0;
    int tradeCountIndex = 0;
    int tradeCountMax = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(t, records[i].name) == 0) {
            existFlag++;
            if (records[i].tradeCount > tradeCountMax) {
                tradeCountMax = records[i].tradeCount;
                tradeCountIndex = i;
            }
        }
    }

    printf("<html>\n");
    printf("<body>\n");
    printf("<div>\n");
    if (existFlag == 0) {
        printf("Ticker %s was not found\n", t);
    }
    else {
        printf("<h1>%s: highest volume</h1>\n", t);
        printf("<div>Day: %d</div>\n", records[tradeCountIndex].index);
        printf("<div>Start price: %.2f</div>\n", records[tradeCountIndex].startValue);
        printf("<div>End price: %.2f</div>\n", records[tradeCountIndex].endValue);
        printf("<div>Volume: ");printWithUnderscores(records[tradeCountIndex].tradeCount);printf("</div>\n");
    }

    printf("</div>\n");
    printf("<table>\n");
    printf("<thead>\n");
    printf("<tr><th>Day</th><th>Ticker</th><th>Start</th><th>End</th><th>Diff</th><th>Volume</th></tr>\n");
    printf("</thead>\n");
    printf("<tbody>\n");
    for (int i = n-1; i >= 0; i--) {
        if (existFlag == 0) {
            printf("<tr>\n");
            printf("\t<td>%d</td>\n", records[i].index);
            printf("\t<td>%s</td>\n", records[i].name);
            printf("\t<td>%.2f</td>\n", records[i].startValue);
            printf("\t<td>%.2f</td>\n", records[i].endValue);
            printf("\t<td>%.2f</td>\n", records[i].sub);
            printf("\t<td>");printWithUnderscores(records[i].tradeCount);printf("</td>\n");
            printf("</tr>\n");
        }
        else {
            if (strcmp(t, records[i].name) == 0) {
                printf("<tr>\n");
                printf("\t<td><b>%d</b></td>\n", records[i].index);
                printf("\t<td><b>%s</b></td>\n", records[i].name);
                printf("\t<td><b>%.2f</b></td>\n", records[i].startValue);
                printf("\t<td><b>%.2f</b></td>\n", records[i].endValue);
                printf("\t<td><b>%.2f</b></td>\n", records[i].sub);
                printf("\t<td><b>");printWithUnderscores(records[i].tradeCount);printf("</b></td>\n");
                printf("</tr>\n");
            }
            else {
                printf("<tr>\n");
                printf("\t<td>%d</td>\n", records[i].index);
                printf("\t<td>%s</td>\n", records[i].name);
                printf("\t<td>%.2f</td>\n", records[i].startValue);
                printf("\t<td>%.2f</td>\n", records[i].endValue);
                printf("\t<td>%.2f</td>\n", records[i].sub);
                printf("\t<td>");printWithUnderscores(records[i].tradeCount);printf("</td>\n");
                printf("</tr>\n");
            }
        }
        
    }
    printf("</tbody>\n");
    printf("</table>\n");
    printf("</body>\n");
    printf("</html>\n");

    for (int i = 0; i < n; i++) {
        free(records[i].name);
    }
    free(records);
    
    return 0;
}

void printWithUnderscores(int number) {
    int temp = number;
    char str[10];
    snprintf(str, sizeof(str), "%d", temp);

    int len = (int)strlen(str);
    for (int i = 0; i < len; i++) {
        printf("%c", str[i]);
        if ((len - i - 1) % 3 == 0 && i != len - 1) {
            printf("_");
        }
    }
}