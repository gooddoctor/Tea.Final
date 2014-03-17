#include <map>

#include <QMediaPlayer>
#include <QString>
#include <QUrl>

namespace staff {
  class Metadata {
  typedef std::map<QUrl, QString> Cache;
  public:
    Metadata();
    static Metadata& comming_in_fast() {
      static Metadata instance;
      return instance;
    }
    QString title(const QUrl& path);
  private:
    Cache cache;
    QMediaPlayer* player;
  };
}
