#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <sstream>
#include "../data/Student.h"
#include "../containers/Sequence.h"
#include "../containers/ListSequence.hpp"
#include "../containers/Histogram.h"
#include "../data/Student.h"
#include "../data/DataGenerator.h"

class HistogramApp : public QWidget {
    Q_OBJECT

public:
    HistogramApp(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Sequence Display Application");

        auto *layout = new QVBoxLayout(this);

        // Input field for sequence size
        auto *inputLayout = new QHBoxLayout();
        QLabel *sizeLabel = new QLabel("Sequence Size:", this);
        sizeInput = new QLineEdit(this);
        inputLayout->addWidget(sizeLabel);
        inputLayout->addWidget(sizeInput);
        layout->addLayout(inputLayout);

        // Input field for histogram range
        auto *rangeLayout = new QHBoxLayout();
        QLabel *rangeLabel = new QLabel("Histogram Range:", this);
        rangeInput = new QLineEdit(this);
        rangeLayout->addWidget(rangeLabel);
        rangeLayout->addWidget(rangeInput);
        layout->addLayout(rangeLayout);

        // Create Integer Sequence Button
        generateIntSequenceButton = new QPushButton("Generate Integer Sequence", this);
        layout->addWidget(generateIntSequenceButton);

        // Connect signal to slot
        connect(generateIntSequenceButton, &QPushButton::clicked, this, &HistogramApp::generateIntSequence);

        // Text field to show the generated sequence
        generatedSequenceText = new QTextEdit(this);
        generatedSequenceText->setReadOnly(true);
        layout->addWidget(generatedSequenceText);

        // Create Histogram Button
        createHistogramButton = new QPushButton("Create Histogram", this);
        layout->addWidget(createHistogramButton);

        // Text field to show the histogram
        histogramText = new QTextEdit(this);
        histogramText->setReadOnly(true);
        layout->addWidget(histogramText);

        connect(createHistogramButton, &QPushButton::clicked, this, &HistogramApp::onCreateHistogramClicked);
    }

private slots:
    void generateIntSequence() {
        bool ok;
        int size = sizeInput->text().toInt(&ok);
        if (!ok || size <= 0) {
            generatedSequenceText->setText("Invalid size.");
            return;
        }

        // Generate integer sequence with a specified range
        int min = 0;  // Adjust as needed
        int max = 100; // Adjust as needed
        intSequence = generateIntegerSequence(size, min, max);
        generatedSequenceText->setText(sequenceToString(intSequence));
    }

    void onCreateHistogramClicked() {
        try {
            bool ok;
            int range = rangeInput->text().toInt(&ok);
            if (!ok || range <= 0) {
                histogramText->setText("Invalid range.");
                return;
            }

            Histogram<int> histogram(intSequence, range);
            histogramText->setText(histogram.histogramToString());
        } catch (const std::exception &e) {
            histogramText->setText(QString("Error creating histogram: %1").arg(e.what()));
        }
    }

private:
    SharedPtr<Sequence<int>> intSequence;

    QLineEdit *sizeInput;
    QLineEdit *rangeInput;
    QTextEdit *generatedSequenceText;
    QTextEdit *histogramText;
    QPushButton *createHistogramButton;
    QPushButton *generateIntSequenceButton;

    QString sequenceToString(SharedPtr<Sequence<int>> seq) {
        std::ostringstream oss;
        for (size_t i = 0; i < seq->getLength(); ++i) {
            if (i > 0) oss << ", ";
            oss << seq->get(i);
        }
        return QString::fromStdString(oss.str());
    }
};
