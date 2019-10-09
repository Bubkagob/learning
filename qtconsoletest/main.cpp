#include <QtCore>

QTextStream cout(stdout, QIODevice::WriteOnly);

int main(int argc, char *argv[]) {
  Q_UNUSED(argc);
  Q_UNUSED(argv);
  QString s1("Hello");
  QString s2{"Qt"};
  cout << (s1 + " " + s2 + "!") << endl;

  QList<QString> list;
  list << s1 << s2;

  QListIterator<QString> iter(list);
  while (iter.hasNext()) {
    cout << iter.next();
    if (iter.hasNext()) {
      cout << " ";
    }
  }

  cout << "!" << endl;

  cout << list.join(" ") + "!" << endl;
}
