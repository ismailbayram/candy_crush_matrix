#include <stdio.h>
#include <time.h>

void print_matrix(char *mat, int m, int n)
{
  int i, j;
  for (i = 0; i < m; i++)
  {
    for (j = 0; j < n; j++)
    {
      printf("%3c", *(mat + i * 50 + j));
    }
    printf("\n");
  }
  printf("\n\n");
}

void init_matrix(char *mat, int *m, int *n) // matrisi ilk baslatma fonksiyonu
{
  int i, j;

  printf("Oyun alanının satır sayısı : ");
  scanf("%d", m);
  printf("Oyun alanının sütun sayısı : ");
  scanf("%d", n);

  for (i = 0; i < *m; i++)
  {
    for (j = 0; j < *n; j++)
    {
      *(mat + i * 50 + j) = rand() % 10 + '0'; // bu elemana 0-9 arasinda rastgele bir sayi ver ve char tipine cevir
    }
  }
  print_matrix(mat, *m, *n);
}

void replace_spaces_with_rand_els(char *mat, int m, int n) // sayilarin alttaki bosluklara dusme fonksiyonu
{
  int i, j, k, spaces, first_spaces, t;
  for (j = 0; j < n; j++)
  {
    i = 0;
    spaces = 0;
    first_spaces = 0;
    for (i = 0; i < m; i++) // sutundaki toplam bosluk sayisi
    {
      if (*(mat + i * 50 + j) == ' ')
      {
        spaces += 1;
      }
    }
    if (spaces > 0) // toplam bosluk sayisi 0 dan buyuk ise
    {
      i = 0;
      while (*(mat + i * 50 + j) == ' ') // yukaridan asaga dogru bir sayiya denk gelene kadar inerek sutundaki bosluklari say
      {
        first_spaces += 1;
        i++;
      }
      i = 0;
      while (first_spaces != spaces && i < m) // yukaridan asaga dogru bir sayiya denk gelene
      // kadar inerek sutundaki bosluk sayisi sutundaki toplam bosluk sayisindan fazla oldugu surece
      {
        k = 0; // sutunu her degistirdikten sonra yukaridaki sart saglanana kadar basa don ve islemleri gerceklestir
        while (k < m)
        {
          if (*(mat + k * 50 + j) != ' ' && *(mat + (k + 1) * 50 + j) == ' ') // eger bir eleman bosluk ve kendisinden sonraki eleman
          // sayi ise yerlerini degistir
          {
            *(mat + (k + 1) * 50 + j) = *(mat + k * 50 + j);
            *(mat + k * 50 + j) = ' ';
          }
          k++;
        }
        t = 0;
        first_spaces = 0;
        while (*(mat + t * 50 + j) == ' ') // dongunun her adiminda yukaridan asaga dogru bir sayiya denk gelene
        // kadar inerek sutundaki bosluk sayisini bul
        {
          first_spaces += 1;
          t++;
        }
        if (first_spaces != spaces) // yukaridan asaga dogru bir sayiya denk gelene
        // kadar inerek sutundaki bosluk sayisi sutundaki toplam bosluk sayisina esit degil ise
        {
          i = 0;
        }
        else
        {
          i++;
        }
      }
    }
  }
  print_matrix(mat, m, n);
}

void fill_in_the_blanks(char *mat, int m, int n) // bosluklari tekrar doldurma fonksiyonu
{
  int i, j;
  for (i = 0; i < m; i++)
  {
    for (j = 0; j < n; j++)
    {
      if (*(mat + i * 50 + j) == ' ') // eger eleman bosluk karakteri ise
      {
        *(mat + i * 50 + j) = rand() % 10 + '0'; // rastgele bir sayi ata
      }
    }
  }
  print_matrix(mat, m, n);
}

void explode_matrix(char *mat, int m, int n, int *score) // yanyana olan elemanlari patlatma fonksiyonu
{
  int i, j, k, current_element, explodable_element = 0;
  char q = 'e'; // devam edip etmeyecegi degisken
  for (i = 0; i < m; i++)
  {
    for (j = 0; j < n; j++)
    {
      current_element = *(mat + i * 50 + j); // dongude dolasirken anlik eleman

      // asagiya dogru
      k = i;                                                       // dongude dolasirken anlik satir numarasi
      while (k < m && *(mat + (k + 1) * 50 + j) == current_element // sagindaki eleman kendisine esitse
             && *(mat + (k + 1) * 50 + j) != ' ')
      { // sagindaki eleman bosluga esit degilse
        if (k == i)
        { // ilk eleman ise
          *(mat + i * 50 + j) = ' ';
          *score += 1;
          explodable_element += 1;
        }
        *(mat + (k + 1) * 50 + j) = ' ';
        k = k + 1;
        *score += 1;
        explodable_element += 1;
      }

      // saga dogru
      k = j;                                                     // dongude dolasirken anlik sutun numarasi
      while (k < n && *(mat + i * 50 + k + 1) == current_element // altindaki eleman kendisine esitse
             && *(mat + i * 50 + k + 1) != ' ')
      { // altindaki eleman bosluga esit degilse
        if (k == j)
        { // ilk eleman ise
          *(mat + i * 50 + j) = ' ';
          *score += 1;
          explodable_element += 1;
        }
        *(mat + i * 50 + k + 1) = ' ';
        k = k + 1;
        *score += 1;
        explodable_element += 1;
      }
    }
  }
  if (explodable_element > 0) // eger patlayabilecek eleman sayisi 0 dan buyuk ise
  {
    getchar();
    print_matrix(mat, m, n);
    getchar();
    replace_spaces_with_rand_els(mat, m, n);
    getchar();
    fill_in_the_blanks(mat, m, n);
    explode_matrix(mat, m, n, score);
  }
  else // degilse
  {
    explodable_element = 0; // patlayabilecek eleman sayisini sifirla
    printf("Devam etmek istiyor musunuz? (e/h)\n");
    scanf(" %c", &q); // kullaniciya sor

    if (q == 'e')
    {
      int x1, y1, x2, y2, temp;
      printf("Yer değiştirilecek elemanların indislerini veriniz\n");
      scanf("%d,%d %d,%d", &x1, &y1, &x2, &y2); // 2 elemanin indislerini al
      temp = *(mat + x1 * 50 + y1);             // 2 elemanin yerlerini degistir
      *(mat + x1 * 50 + y1) = *(mat + x2 * 50 + y2);
      *(mat + x2 * 50 + y2) = temp;
      print_matrix(mat, m, n);
      getchar();
      explode_matrix(mat, m, n, score); // fonksiyonu tekrar calistir.
    }
  }
}

int main()
{
  srand(time(NULL));   // rastgele sayi almak icin calistirilan fonksiyon
  int m, n, score = 0; // satir, sutun, puan ve patlayabilecek eleman sayisi degiskenleri
  char mat[50][50];    // matris tanimi

  init_matrix(&mat[0][0], &m, &n);

  explode_matrix(&mat[0][0], m, n, &score);

  printf("\n\n PUANINIZ : %d\n\n", score * score);

  return 0;
}