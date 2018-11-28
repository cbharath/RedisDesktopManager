#pragma once
#include <qredisclient/connection.h>
#include <QFuture>
#include <QMap>
#include <QSharedPointer>
#include <QString>
#include <QStringList>
#include <functional>
#include "exception.h"

namespace Console {
class Operations;
}

namespace ConnectionsTree {

class KeyItem;
class NamespaceItem;
class AbstractNamespaceItem;

class Operations {
  ADD_EXCEPTION
 public:
  /**
   * List of databases with keys counters
   * @emit databesesLoaded
   **/
  virtual QFuture<bool> getDatabases(std::function<void(QMap<int, int>)>) = 0;

  /**
   * @brief loadNamespaceItems
   * @param dbIndex
   * @param filter
   * @param callback
   */
  virtual void loadNamespaceItems(
      QSharedPointer<AbstractNamespaceItem> parent, const QString& filter,
      std::function<void(const QString& err)> callback,
      QSet<QByteArray> expandedNs) = 0;

  /**
   * Cancel all operations & close connection
   * @brief disconnect
   */
  virtual void disconnect() = 0;

  /**
   * @brief getNamespaceSeparator
   * @return
   */
  virtual QString getNamespaceSeparator() = 0;

  virtual QString defaultFilter() = 0;

  virtual void openKeyTab(QSharedPointer<KeyItem> key, bool openInNewTab) = 0;

  virtual void openConsoleTab(int dbIndex = 0) = 0;

  virtual void openNewKeyDialog(int dbIndex, std::function<void()> callback,
                                QString keyPrefix = QString()) = 0;

  virtual void openServerStats() = 0;

  virtual void duplicateConnection() = 0;

  virtual void notifyDbWasUnloaded(int dbIndex) = 0;

  virtual void deleteDbKey(ConnectionsTree::KeyItem& key,
                           std::function<void(const QString&)> callback) = 0;

  virtual void deleteDbNamespace(ConnectionsTree::NamespaceItem& ns) = 0;

  virtual void flushDb(int dbIndex,
                       std::function<void(const QString&)> callback) = 0;

  virtual QString mode() = 0;

  virtual bool isConnected() const = 0;

  virtual ~Operations() {}
};
}  // namespace ConnectionsTree
