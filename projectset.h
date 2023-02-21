#ifndef PROJECTSET_H
#define PROJECTSET_H

#include <QVector>



class ProjectSet
{
public:
    ProjectSet();
    ProjectSet(const QString &projectType, const QString &projectName, int projectId, int unitId, const QVector<qreal> &prePrices, int prePricesStartYear, const QVector<qreal> &firstUnitPrices, int firstUnitStartYear, const QVector<qreal> &lastUnitPrices, int lastUnitStartYear, const QVector<qreal> &postPrices, int postPricesStartYear, const QVector<qreal> &serialPrices, int serialPricesStartYear);
    ProjectSet(const QString &projectType, const QString &projectName, int projectId, int unitId, const QVector<int> &EDWLaunchYears, const QVector<int> &seriesLaunchYears, const QVector<qreal> &spacecraftPrices, const QVector<QString> &boosterRockets, const QVector<int> &spacecraftBlocks, const QVector<qreal> &boosterRocketPrices, const QVector<qreal> &prePrices, int prePricesStartYear, const QVector<qreal> &firstUnitPrices, int firstUnitStartYear, const QVector<qreal> &lastUnitPrices, int lastUnitStartYear, const QVector<qreal> &postPrices, int postPricesStartYear, const QVector<qreal> &serialPrices, int serialPricesStartYear);

    const QVector<int> &getEDWLaunchYears() const;
    void setEDWLaunchYears(const QVector<int> &newEDWLaunchYears);
    const QVector<int> &getSeriesLaunchYears() const;
    void setSeriesLaunchYears(const QVector<int> &newSeriesLaunchYears);
    const QVector<qreal> &getSpacecraftPrices() const;
    void setSpacecraftPrices(const QVector<qreal> &newSpacecraftPrices);
    const QVector<QString> &getBoosterRockets() const;
    void setBoosterRockets(const QVector<QString> &newBoosterRockets);
    const QVector<int> &getSpacecraftBlocks() const;
    void setSpacecraftBlocks(const QVector<int> &newSpacecraftBlocks);
    const QVector<qreal> &getBoosterRocketPrices() const;
    void setBoosterRocketPrices(const QVector<qreal> &newBoosterRocketPrices);
    const QVector<qreal> &getPrePrices() const;
    void setPrePrices(const QVector<qreal> &newPrePrices);
    int getPrePricesStartYear() const;
    void setPrePricesStartYear(int newPrePricesStartYear);
    const QVector<qreal> &getFirstUnitPrices() const;
    void setFirstUnitPrices(const QVector<qreal> &newFirstUnitPrices);
    int getFirstUnitStartYear() const;
    void setFirstUnitStartYear(int newFirstUnitStartYear);
    const QVector<qreal> &getLastUnitPrices() const;
    void setLastUnitPrices(const QVector<qreal> &newLastUnitPrices);
    int getLastUnitStartYear() const;
    void setLastUnitStartYear(int newLastUnitStartYear);
    const QVector<qreal> &getPostPrices() const;
    void setPostPrices(const QVector<qreal> &newPostPrices);
    int getPostPricesStartYear() const;
    void setPostPricesStartYear(int newPostPricesStartYear);
    const QVector<qreal> &getSerialPrices() const;
    void setSerialPrices(const QVector<qreal> &newSerialPrices);
    int getSerialPricesStartYear() const;
    void setSerialPricesStartYear(int newSerialPricesStartYear);

    const QString &getProjectType() const;
    void setProjectType(const QString &newProjectType);
    const QString &getProjectName() const;
    void setProjectName(const QString &newProjectName);
    int getProjectId() const;
    void setProjectId(int newProjectId);
    int getUnitId() const;
    void setUnitId(int newUnitId);

protected:
    QString projectType;
    QString projectName;
    int projectId;
    int unitId;

    QVector <int> EDWLaunchYears;
    QVector <int> seriesLaunchYears;
    QVector <qreal> spacecraftPrices;
    QVector <QString> boosterRockets;
    QVector <int> spacecraftBlocks;
    QVector <qreal> boosterRocketPrices;

    QVector <qreal> prePrices;
    int prePricesStartYear;
    QVector <qreal> firstUnitPrices;
    int firstUnitStartYear;
    QVector <qreal> lastUnitPrices;
    int lastUnitStartYear;
    QVector <qreal> postPrices;
    int postPricesStartYear;
    QVector <qreal> serialPrices;
    int serialPricesStartYear;
};

#endif // PROJECTSET_H
