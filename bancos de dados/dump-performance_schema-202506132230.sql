/*M!999999\- enable the sandbox mode */ 
-- MariaDB dump 10.19-11.8.2-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: performance_schema
-- ------------------------------------------------------
-- Server version	11.8.2-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*M!100616 SET @OLD_NOTE_VERBOSITY=@@NOTE_VERBOSITY, NOTE_VERBOSITY=0 */;

--
-- Table structure for table `accounts`
--

DROP TABLE IF EXISTS `accounts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `accounts` (
  `USER` char(128) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'The connection''s client user name for the connection, or NULL if an internal thread.',
  `HOST` char(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'The connection client''s host name, or NULL if an internal thread.',
  `CURRENT_CONNECTIONS` bigint(20) NOT NULL COMMENT 'Current connections for the account.',
  `TOTAL_CONNECTIONS` bigint(20) NOT NULL COMMENT 'Total connections for the account.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `accounts`
--

LOCK TABLES `accounts` WRITE;
/*!40000 ALTER TABLE `accounts` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `accounts` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `cond_instances`
--

DROP TABLE IF EXISTS `cond_instances`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `cond_instances` (
  `NAME` varchar(128) NOT NULL COMMENT 'Client user name for the connection, or NULL if an internal thread.',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned NOT NULL COMMENT 'Address in memory of the instrumented condition.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cond_instances`
--

LOCK TABLES `cond_instances` WRITE;
/*!40000 ALTER TABLE `cond_instances` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `cond_instances` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_stages_current`
--

DROP TABLE IF EXISTS `events_stages_current`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_stages_current` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread associated with the event. Together with EVENT_ID uniquely identifies the row.',
  `EVENT_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread''s current event number at the start of the event. Together with THREAD_ID uniquely identifies the row.',
  `END_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'NULL when the event starts, set to the thread''s current event number at the end of the event.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event instrument name and a NAME from the setup_instruments table',
  `SOURCE` varchar(64) DEFAULT NULL COMMENT 'Name and line number of the source file containing the instrumented code that produced the event.',
  `TIMER_START` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing started or NULL if timing is not collected.',
  `TIMER_END` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing ended, or NULL if the event has not ended or timing is not collected.',
  `TIMER_WAIT` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds of the event''s duration or NULL if the event has not ended or timing is not collected.',
  `WORK_COMPLETED` bigint(20) unsigned DEFAULT NULL COMMENT 'The number of work units completed for the stage. NULL if the stage event progress is not instrumented.',
  `WORK_ESTIMATED` bigint(20) unsigned DEFAULT NULL COMMENT 'The number of work units expected for the stage. NULL if the stage event progress is not instrumented.',
  `NESTING_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'EVENT_ID of event within which this event nests.',
  `NESTING_EVENT_TYPE` enum('TRANSACTION','STATEMENT','STAGE','WAIT') DEFAULT NULL COMMENT 'Nesting event type. Either transaction, statement, stage or wait.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_stages_current`
--

LOCK TABLES `events_stages_current` WRITE;
/*!40000 ALTER TABLE `events_stages_current` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_stages_current` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_stages_history`
--

DROP TABLE IF EXISTS `events_stages_history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_stages_history` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread associated with the event. Together with EVENT_ID uniquely identifies the row.',
  `EVENT_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread''s current event number at the start of the event. Together with THREAD_ID uniquely identifies the row.',
  `END_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'NULL when the event starts, set to the thread''s current event number at the end of the event.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event instrument name and a NAME from the setup_instruments table',
  `SOURCE` varchar(64) DEFAULT NULL COMMENT 'Name and line number of the source file containing the instrumented code that produced the event.',
  `TIMER_START` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing started or NULL if timing is not collected.',
  `TIMER_END` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing ended, or NULL if the event has not ended or timing is not collected.',
  `TIMER_WAIT` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds of the event''s duration or NULL if the event has not ended or timing is not collected.',
  `WORK_COMPLETED` bigint(20) unsigned DEFAULT NULL COMMENT 'The number of work units completed for the stage. NULL if the stage event progress is not instrumented.',
  `WORK_ESTIMATED` bigint(20) unsigned DEFAULT NULL COMMENT 'The number of work units expected for the stage. NULL if the stage event progress is not instrumented.',
  `NESTING_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'EVENT_ID of event within which this event nests.',
  `NESTING_EVENT_TYPE` enum('TRANSACTION','STATEMENT','STAGE','WAIT') DEFAULT NULL COMMENT 'Nesting event type. Either transaction, statement, stage or wait.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_stages_history`
--

LOCK TABLES `events_stages_history` WRITE;
/*!40000 ALTER TABLE `events_stages_history` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_stages_history` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_stages_history_long`
--

DROP TABLE IF EXISTS `events_stages_history_long`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_stages_history_long` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread associated with the event. Together with EVENT_ID uniquely identifies the row.',
  `EVENT_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread''s current event number at the start of the event. Together with THREAD_ID uniquely identifies the row.',
  `END_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'NULL when the event starts, set to the thread''s current event number at the end of the event.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event instrument name and a NAME from the setup_instruments table',
  `SOURCE` varchar(64) DEFAULT NULL COMMENT 'Name and line number of the source file containing the instrumented code that produced the event.',
  `TIMER_START` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing started or NULL if timing is not collected.',
  `TIMER_END` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing ended, or NULL if the event has not ended or timing is not collected.',
  `TIMER_WAIT` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds of the event''s duration or NULL if the event has not ended or timing is not collected.',
  `WORK_COMPLETED` bigint(20) unsigned DEFAULT NULL COMMENT 'The number of work units completed for the stage. NULL if the stage event progress is not instrumented.',
  `WORK_ESTIMATED` bigint(20) unsigned DEFAULT NULL COMMENT 'The number of work units expected for the stage. NULL if the stage event progress is not instrumented.',
  `NESTING_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'EVENT_ID of event within which this event nests.',
  `NESTING_EVENT_TYPE` enum('TRANSACTION','STATEMENT','STAGE','WAIT') DEFAULT NULL COMMENT 'Nesting event type. Either transaction, statement, stage or wait.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_stages_history_long`
--

LOCK TABLES `events_stages_history_long` WRITE;
/*!40000 ALTER TABLE `events_stages_history_long` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_stages_history_long` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_stages_summary_by_account_by_event_name`
--

DROP TABLE IF EXISTS `events_stages_summary_by_account_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_stages_summary_by_account_by_event_name` (
  `USER` char(128) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'User. Used together with HOST and EVENT_NAME for grouping events.',
  `HOST` char(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'Host. Used together with USER and EVENT_NAME for grouping events.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name. Used together with USER and HOST for grouping events.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events, which includes all timed and untimed events.',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the timed summarized events.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the timed summarized events.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the timed summarized events.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the timed summarized events.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_stages_summary_by_account_by_event_name`
--

LOCK TABLES `events_stages_summary_by_account_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_stages_summary_by_account_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_stages_summary_by_account_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_stages_summary_by_host_by_event_name`
--

DROP TABLE IF EXISTS `events_stages_summary_by_host_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_stages_summary_by_host_by_event_name` (
  `HOST` char(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'Host. Used together with EVENT_NAME for grouping events.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name. Used together with HOST for grouping events.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events, which includes all timed and untimed events.',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the timed summarized events.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the timed summarized events.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the timed summarized events.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the timed summarized events.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_stages_summary_by_host_by_event_name`
--

LOCK TABLES `events_stages_summary_by_host_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_stages_summary_by_host_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_stages_summary_by_host_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_stages_summary_by_thread_by_event_name`
--

DROP TABLE IF EXISTS `events_stages_summary_by_thread_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_stages_summary_by_thread_by_event_name` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread associated with the event. Together with EVENT_NAME uniquely identifies the row.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name. Used together with THREAD_ID for grouping events.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events, which includes all timed and untimed events.',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the timed summarized events.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the timed summarized events.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the timed summarized events.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the timed summarized events.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_stages_summary_by_thread_by_event_name`
--

LOCK TABLES `events_stages_summary_by_thread_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_stages_summary_by_thread_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_stages_summary_by_thread_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_stages_summary_by_user_by_event_name`
--

DROP TABLE IF EXISTS `events_stages_summary_by_user_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_stages_summary_by_user_by_event_name` (
  `USER` char(128) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'User. Used together with EVENT_NAME for grouping events.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name. Used together with USER for grouping events.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events, which includes all timed and untimed events.',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the timed summarized events.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the timed summarized events.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the timed summarized events.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the timed summarized events.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_stages_summary_by_user_by_event_name`
--

LOCK TABLES `events_stages_summary_by_user_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_stages_summary_by_user_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_stages_summary_by_user_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_stages_summary_global_by_event_name`
--

DROP TABLE IF EXISTS `events_stages_summary_global_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_stages_summary_global_by_event_name` (
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events, which includes all timed and untimed events.',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the timed summarized events.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the timed summarized events.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the timed summarized events.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the timed summarized events.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_stages_summary_global_by_event_name`
--

LOCK TABLES `events_stages_summary_global_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_stages_summary_global_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_stages_summary_global_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_statements_current`
--

DROP TABLE IF EXISTS `events_statements_current`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_statements_current` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread associated with the event. Together with EVENT_ID uniquely identifies the row.',
  `EVENT_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread''s current event number at the start of the event. Together with THREAD_ID uniquely identifies the row.',
  `END_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'NULL when the event starts, set to the thread''s current event number at the end of the event.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event instrument name and a NAME from the setup_instruments table',
  `SOURCE` varchar(64) DEFAULT NULL COMMENT 'Name and line number of the source file containing the instrumented code that produced the event.',
  `TIMER_START` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing started or NULL if timing is not collected.',
  `TIMER_END` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing ended, or NULL if the event has not ended or timing is not collected.',
  `TIMER_WAIT` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds of the event''s duration or NULL if the event has not ended or timing is not collected.',
  `LOCK_TIME` bigint(20) unsigned NOT NULL COMMENT 'Time in picoseconds spent waiting for locks. The time is calculated in microseconds but stored in picoseconds for compatibility with other timings.',
  `SQL_TEXT` longtext DEFAULT NULL COMMENT 'The SQL statement, or NULL if the command is not associated with an SQL statement.',
  `DIGEST` varchar(32) DEFAULT NULL COMMENT 'Statement digest.',
  `DIGEST_TEXT` longtext DEFAULT NULL COMMENT 'Statement digest text.',
  `CURRENT_SCHEMA` varchar(64) DEFAULT NULL COMMENT 'Statement''s default database for the statement, or NULL if there was none.',
  `OBJECT_TYPE` varchar(64) DEFAULT NULL COMMENT 'NULL for top level statements. The parent statement object type for nested statements (stored programs).',
  `OBJECT_SCHEMA` varchar(64) DEFAULT NULL COMMENT 'NULL for top level statements. The parent statement object schema for nested statements (stored programs).',
  `OBJECT_NAME` varchar(64) DEFAULT NULL COMMENT 'NULL for top level statements. The parent statement object name for nested statements (stored programs).',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned DEFAULT NULL COMMENT 'Address in memory of the statement object.',
  `MYSQL_ERRNO` int(11) DEFAULT NULL COMMENT 'Error code. See MariaDB Error Codes for a full list.',
  `RETURNED_SQLSTATE` varchar(5) DEFAULT NULL COMMENT 'The SQLSTATE value.',
  `MESSAGE_TEXT` varchar(128) DEFAULT NULL COMMENT 'Statement error message. See MariaDB Error Codes.',
  `ERRORS` bigint(20) unsigned NOT NULL COMMENT '0 if SQLSTATE signifies completion (starting with 00) or warning (01), otherwise 1.',
  `WARNINGS` bigint(20) unsigned NOT NULL COMMENT 'Number of warnings from the diagnostics area.',
  `ROWS_AFFECTED` bigint(20) unsigned NOT NULL COMMENT 'Number of rows affected the statement affected.',
  `ROWS_SENT` bigint(20) unsigned NOT NULL COMMENT 'Number of rows returned.',
  `ROWS_EXAMINED` bigint(20) unsigned NOT NULL COMMENT 'Number of rows read during the statement''s execution.',
  `CREATED_TMP_DISK_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Number of on-disk temp tables created by the statement.',
  `CREATED_TMP_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Number of temp tables created by the statement.',
  `SELECT_FULL_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Number of joins performed by the statement which did not use an index.',
  `SELECT_FULL_RANGE_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Number of joins performed by the statement which used a range search of the first table.',
  `SELECT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Number of joins performed by the statement which used a range of the first table.',
  `SELECT_RANGE_CHECK` bigint(20) unsigned NOT NULL COMMENT 'Number of joins without keys performed by the statement that check for key usage after each row.',
  `SELECT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Number of joins performed by the statement which used a full scan of the first table.',
  `SORT_MERGE_PASSES` bigint(20) unsigned NOT NULL COMMENT 'Number of merge passes by the sort algorithm performed by the statement. If too high, you may need to increase the sort_buffer_size.',
  `SORT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Number of sorts performed by the statement which used a range.',
  `SORT_ROWS` bigint(20) unsigned NOT NULL COMMENT 'Number of rows sorted by the statement.',
  `SORT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Number of sorts performed by the statement which used a full table scan.',
  `NO_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT '0 if the statement performed a table scan with an index, 1 if without an index.',
  `NO_GOOD_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT '0 if a good index was found for the statement, 1 if no good index was found. See the Range checked for each record description in the EXPLAIN article.',
  `NESTING_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'NULL for top level statements. The parent statement event id for nested statements (stored programs).',
  `NESTING_EVENT_TYPE` enum('TRANSACTION','STATEMENT','STAGE','WAIT') DEFAULT NULL COMMENT 'NULL for top level statements. The parent statement event type for nested statements (stored programs).',
  `NESTING_EVENT_LEVEL` int(11) DEFAULT NULL COMMENT '0 for top level statements. The parent statement level plus 1 for nested statements (stored programs).'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_statements_current`
--

LOCK TABLES `events_statements_current` WRITE;
/*!40000 ALTER TABLE `events_statements_current` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_statements_current` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_statements_history`
--

DROP TABLE IF EXISTS `events_statements_history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_statements_history` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread associated with the event. Together with EVENT_ID uniquely identifies the row.',
  `EVENT_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread''s current event number at the start of the event. Together with THREAD_ID uniquely identifies the row.',
  `END_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'NULL when the event starts, set to the thread''s current event number at the end of the event.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event instrument name and a NAME from the setup_instruments table',
  `SOURCE` varchar(64) DEFAULT NULL COMMENT 'Name and line number of the source file containing the instrumented code that produced the event.',
  `TIMER_START` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing started or NULL if timing is not collected.',
  `TIMER_END` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing ended, or NULL if the event has not ended or timing is not collected.',
  `TIMER_WAIT` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds of the event''s duration or NULL if the event has not ended or timing is not collected.',
  `LOCK_TIME` bigint(20) unsigned NOT NULL COMMENT 'Time in picoseconds spent waiting for locks. The time is calculated in microseconds but stored in picoseconds for compatibility with other timings.',
  `SQL_TEXT` longtext DEFAULT NULL COMMENT 'The SQL statement, or NULL if the command is not associated with an SQL statement.',
  `DIGEST` varchar(32) DEFAULT NULL COMMENT 'Statement digest.',
  `DIGEST_TEXT` longtext DEFAULT NULL COMMENT 'Statement digest text.',
  `CURRENT_SCHEMA` varchar(64) DEFAULT NULL COMMENT 'Statement''s default database for the statement, or NULL if there was none.',
  `OBJECT_TYPE` varchar(64) DEFAULT NULL COMMENT 'NULL for top level statements. The parent statement object type for nested statements (stored programs).',
  `OBJECT_SCHEMA` varchar(64) DEFAULT NULL COMMENT 'NULL for top level statements. The parent statement object schema for nested statements (stored programs).',
  `OBJECT_NAME` varchar(64) DEFAULT NULL COMMENT 'NULL for top level statements. The parent statement object name for nested statements (stored programs).',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned DEFAULT NULL COMMENT 'Address in memory of the statement object.',
  `MYSQL_ERRNO` int(11) DEFAULT NULL COMMENT 'Error code. See MariaDB Error Codes for a full list.',
  `RETURNED_SQLSTATE` varchar(5) DEFAULT NULL COMMENT 'The SQLSTATE value.',
  `MESSAGE_TEXT` varchar(128) DEFAULT NULL COMMENT 'Statement error message. See MariaDB Error Codes.',
  `ERRORS` bigint(20) unsigned NOT NULL COMMENT '0 if SQLSTATE signifies completion (starting with 00) or warning (01), otherwise 1.',
  `WARNINGS` bigint(20) unsigned NOT NULL COMMENT 'Number of warnings from the diagnostics area.',
  `ROWS_AFFECTED` bigint(20) unsigned NOT NULL COMMENT 'Number of rows affected the statement affected.',
  `ROWS_SENT` bigint(20) unsigned NOT NULL COMMENT 'Number of rows returned.',
  `ROWS_EXAMINED` bigint(20) unsigned NOT NULL COMMENT 'Number of rows read during the statement''s execution.',
  `CREATED_TMP_DISK_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Number of on-disk temp tables created by the statement.',
  `CREATED_TMP_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Number of temp tables created by the statement.',
  `SELECT_FULL_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Number of joins performed by the statement which did not use an index.',
  `SELECT_FULL_RANGE_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Number of joins performed by the statement which used a range search of the first table.',
  `SELECT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Number of joins performed by the statement which used a range of the first table.',
  `SELECT_RANGE_CHECK` bigint(20) unsigned NOT NULL COMMENT 'Number of joins without keys performed by the statement that check for key usage after each row.',
  `SELECT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Number of joins performed by the statement which used a full scan of the first table.',
  `SORT_MERGE_PASSES` bigint(20) unsigned NOT NULL COMMENT 'Number of merge passes by the sort algorithm performed by the statement. If too high, you may need to increase the sort_buffer_size.',
  `SORT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Number of sorts performed by the statement which used a range.',
  `SORT_ROWS` bigint(20) unsigned NOT NULL COMMENT 'Number of rows sorted by the statement.',
  `SORT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Number of sorts performed by the statement which used a full table scan.',
  `NO_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT '0 if the statement performed a table scan with an index, 1 if without an index.',
  `NO_GOOD_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT '0 if a good index was found for the statement, 1 if no good index was found. See the Range checked for each record description in the EXPLAIN article.',
  `NESTING_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'NULL for top level statements. The parent statement event id for nested statements (stored programs).',
  `NESTING_EVENT_TYPE` enum('TRANSACTION','STATEMENT','STAGE','WAIT') DEFAULT NULL COMMENT 'NULL for top level statements. The parent statement event type for nested statements (stored programs).',
  `NESTING_EVENT_LEVEL` int(11) DEFAULT NULL COMMENT '0 for top level statements. The parent statement level plus 1 for nested statements (stored programs).'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_statements_history`
--

LOCK TABLES `events_statements_history` WRITE;
/*!40000 ALTER TABLE `events_statements_history` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_statements_history` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_statements_history_long`
--

DROP TABLE IF EXISTS `events_statements_history_long`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_statements_history_long` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread associated with the event. Together with EVENT_ID uniquely identifies the row.',
  `EVENT_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread''s current event number at the start of the event. Together with THREAD_ID uniquely identifies the row.',
  `END_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'NULL when the event starts, set to the thread''s current event number at the end of the event.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event instrument name and a NAME from the setup_instruments table',
  `SOURCE` varchar(64) DEFAULT NULL COMMENT 'Name and line number of the source file containing the instrumented code that produced the event.',
  `TIMER_START` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing started or NULL if timing is not collected.',
  `TIMER_END` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing ended, or NULL if the event has not ended or timing is not collected.',
  `TIMER_WAIT` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds of the event''s duration or NULL if the event has not ended or timing is not collected.',
  `LOCK_TIME` bigint(20) unsigned NOT NULL COMMENT 'Time in picoseconds spent waiting for locks. The time is calculated in microseconds but stored in picoseconds for compatibility with other timings.',
  `SQL_TEXT` longtext DEFAULT NULL COMMENT 'The SQL statement, or NULL if the command is not associated with an SQL statement.',
  `DIGEST` varchar(32) DEFAULT NULL COMMENT 'Statement digest.',
  `DIGEST_TEXT` longtext DEFAULT NULL COMMENT 'Statement digest text.',
  `CURRENT_SCHEMA` varchar(64) DEFAULT NULL COMMENT 'Statement''s default database for the statement, or NULL if there was none.',
  `OBJECT_TYPE` varchar(64) DEFAULT NULL COMMENT 'NULL for top level statements. The parent statement object type for nested statements (stored programs).',
  `OBJECT_SCHEMA` varchar(64) DEFAULT NULL COMMENT 'NULL for top level statements. The parent statement object schema for nested statements (stored programs).',
  `OBJECT_NAME` varchar(64) DEFAULT NULL COMMENT 'NULL for top level statements. The parent statement object name for nested statements (stored programs).',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned DEFAULT NULL COMMENT 'Address in memory of the statement object.',
  `MYSQL_ERRNO` int(11) DEFAULT NULL COMMENT 'Error code. See MariaDB Error Codes for a full list.',
  `RETURNED_SQLSTATE` varchar(5) DEFAULT NULL COMMENT 'The SQLSTATE value.',
  `MESSAGE_TEXT` varchar(128) DEFAULT NULL COMMENT 'Statement error message. See MariaDB Error Codes.',
  `ERRORS` bigint(20) unsigned NOT NULL COMMENT '0 if SQLSTATE signifies completion (starting with 00) or warning (01), otherwise 1.',
  `WARNINGS` bigint(20) unsigned NOT NULL COMMENT 'Number of warnings from the diagnostics area.',
  `ROWS_AFFECTED` bigint(20) unsigned NOT NULL COMMENT 'Number of rows affected the statement affected.',
  `ROWS_SENT` bigint(20) unsigned NOT NULL COMMENT 'Number of rows returned.',
  `ROWS_EXAMINED` bigint(20) unsigned NOT NULL COMMENT 'Number of rows read during the statement''s execution.',
  `CREATED_TMP_DISK_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Number of on-disk temp tables created by the statement.',
  `CREATED_TMP_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Number of temp tables created by the statement.',
  `SELECT_FULL_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Number of joins performed by the statement which did not use an index.',
  `SELECT_FULL_RANGE_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Number of joins performed by the statement which used a range search of the first table.',
  `SELECT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Number of joins performed by the statement which used a range of the first table.',
  `SELECT_RANGE_CHECK` bigint(20) unsigned NOT NULL COMMENT 'Number of joins without keys performed by the statement that check for key usage after each row.',
  `SELECT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Number of joins performed by the statement which used a full scan of the first table.',
  `SORT_MERGE_PASSES` bigint(20) unsigned NOT NULL COMMENT 'Number of merge passes by the sort algorithm performed by the statement. If too high, you may need to increase the sort_buffer_size.',
  `SORT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Number of sorts performed by the statement which used a range.',
  `SORT_ROWS` bigint(20) unsigned NOT NULL COMMENT 'Number of rows sorted by the statement.',
  `SORT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Number of sorts performed by the statement which used a full table scan.',
  `NO_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT '0 if the statement performed a table scan with an index, 1 if without an index.',
  `NO_GOOD_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT '0 if a good index was found for the statement, 1 if no good index was found. See the Range checked for each record description in the EXPLAIN article.',
  `NESTING_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'NULL for top level statements. The parent statement event id for nested statements (stored programs).',
  `NESTING_EVENT_TYPE` enum('TRANSACTION','STATEMENT','STAGE','WAIT') DEFAULT NULL COMMENT 'NULL for top level statements. The parent statement event type for nested statements (stored programs).',
  `NESTING_EVENT_LEVEL` int(11) DEFAULT NULL COMMENT '0 for top level statements. The parent statement level plus 1 for nested statements (stored programs).'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_statements_history_long`
--

LOCK TABLES `events_statements_history_long` WRITE;
/*!40000 ALTER TABLE `events_statements_history_long` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_statements_history_long` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_statements_summary_by_account_by_event_name`
--

DROP TABLE IF EXISTS `events_statements_summary_by_account_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_statements_summary_by_account_by_event_name` (
  `USER` char(128) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'User. Used together with HOST and EVENT_NAME for grouping events.',
  `HOST` char(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'Host. Used together with USER and EVENT_NAME for grouping events.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name. Used together with USER and HOST for grouping events.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.',
  `SUM_LOCK_TIME` bigint(20) unsigned NOT NULL COMMENT 'Sum of the LOCK_TIME column in the events_statements_current table.',
  `SUM_ERRORS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ERRORS column in the events_statements_current table.',
  `SUM_WARNINGS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the WARNINGS column in the events_statements_current table.',
  `SUM_ROWS_AFFECTED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_AFFECTED column in the events_statements_current table.',
  `SUM_ROWS_SENT` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_SENT column in the events_statements_current table.',
  `SUM_ROWS_EXAMINED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_EXAMINED column in the events_statements_current table.',
  `SUM_CREATED_TMP_DISK_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the CREATED_TMP_DISK_TABLES column in the events_statements_current table.',
  `SUM_CREATED_TMP_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the CREATED_TMP_TABLES column in the events_statements_current table.',
  `SUM_SELECT_FULL_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_FULL_JOIN column in the events_statements_current table.',
  `SUM_SELECT_FULL_RANGE_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_FULL_RANGE_JOIN column in the events_statements_current table.',
  `SUM_SELECT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_RANGE column in the events_statements_current table.',
  `SUM_SELECT_RANGE_CHECK` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_RANGE_CHECK column in the events_statements_current table.',
  `SUM_SELECT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_SCAN column in the events_statements_current table.',
  `SUM_SORT_MERGE_PASSES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_MERGE_PASSES column in the events_statements_current table.',
  `SUM_SORT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_RANGE column in the events_statements_current table.',
  `SUM_SORT_ROWS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_ROWS column in the events_statements_current table.',
  `SUM_SORT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_SCAN column in the events_statements_current table.',
  `SUM_NO_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the NO_INDEX_USED column in the events_statements_current table.',
  `SUM_NO_GOOD_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the NO_GOOD_INDEX_USED column in the events_statements_current table.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_statements_summary_by_account_by_event_name`
--

LOCK TABLES `events_statements_summary_by_account_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_statements_summary_by_account_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_statements_summary_by_account_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_statements_summary_by_digest`
--

DROP TABLE IF EXISTS `events_statements_summary_by_digest`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_statements_summary_by_digest` (
  `SCHEMA_NAME` varchar(64) DEFAULT NULL COMMENT 'Database name. Records are summarised together with DIGEST.',
  `DIGEST` varchar(32) DEFAULT NULL COMMENT 'Performance Schema digest. Records are summarised together with SCHEMA NAME.',
  `DIGEST_TEXT` longtext DEFAULT NULL COMMENT 'The unhashed form of the digest.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.',
  `SUM_LOCK_TIME` bigint(20) unsigned NOT NULL COMMENT 'Sum of the LOCK_TIME column in the events_statements_current table.',
  `SUM_ERRORS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ERRORS column in the events_statements_current table.',
  `SUM_WARNINGS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the WARNINGS column in the events_statements_current table.',
  `SUM_ROWS_AFFECTED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_AFFECTED column in the events_statements_current table.',
  `SUM_ROWS_SENT` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_SENT column in the events_statements_current table.',
  `SUM_ROWS_EXAMINED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_EXAMINED column in the events_statements_current table.',
  `SUM_CREATED_TMP_DISK_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the CREATED_TMP_DISK_TABLES column in the events_statements_current table.',
  `SUM_CREATED_TMP_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the CREATED_TMP_TABLES column in the events_statements_current table.',
  `SUM_SELECT_FULL_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_FULL_JOIN column in the events_statements_current table.',
  `SUM_SELECT_FULL_RANGE_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_FULL_RANGE_JOIN column in the events_statements_current table.',
  `SUM_SELECT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_RANGE column in the events_statements_current table.',
  `SUM_SELECT_RANGE_CHECK` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_RANGE_CHECK column in the events_statements_current table.',
  `SUM_SELECT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_SCAN column in the events_statements_current table.',
  `SUM_SORT_MERGE_PASSES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_MERGE_PASSES column in the events_statements_current table.',
  `SUM_SORT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_RANGE column in the events_statements_current table.',
  `SUM_SORT_ROWS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_ROWS column in the events_statements_current table.',
  `SUM_SORT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_SCAN column in the events_statements_current table.',
  `SUM_NO_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the NO_INDEX_USED column in the events_statements_current table.',
  `SUM_NO_GOOD_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the NO_GOOD_INDEX_USED column in the events_statements_current table.',
  `FIRST_SEEN` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'Time at which the digest was first seen.',
  `LAST_SEEN` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'Time at which the digest was most recently seen.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_statements_summary_by_digest`
--

LOCK TABLES `events_statements_summary_by_digest` WRITE;
/*!40000 ALTER TABLE `events_statements_summary_by_digest` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_statements_summary_by_digest` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_statements_summary_by_host_by_event_name`
--

DROP TABLE IF EXISTS `events_statements_summary_by_host_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_statements_summary_by_host_by_event_name` (
  `HOST` char(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'Host. Used together with EVENT_NAME for grouping events.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name. Used together with HOST for grouping events.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.',
  `SUM_LOCK_TIME` bigint(20) unsigned NOT NULL COMMENT 'Sum of the LOCK_TIME column in the events_statements_currentd table.',
  `SUM_ERRORS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ERRORS column in the events_statements_current table.',
  `SUM_WARNINGS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the WARNINGS column in the events_statements_current table.',
  `SUM_ROWS_AFFECTED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_AFFECTED column in the events_statements_current table.',
  `SUM_ROWS_SENT` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_SENT column in the events_statements_current table.',
  `SUM_ROWS_EXAMINED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_EXAMINED column in the events_statements_current table.',
  `SUM_CREATED_TMP_DISK_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the CREATED_TMP_DISK_TABLES column in the events_statements_current table.',
  `SUM_CREATED_TMP_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the CREATED_TMP_TABLES column in the events_statements_current table.',
  `SUM_SELECT_FULL_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_FULL_JOIN column in the events_statements_current table.',
  `SUM_SELECT_FULL_RANGE_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_FULL_RANGE_JOINW column in the events_statements_current table.',
  `SUM_SELECT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_RANGE column in the events_statements_current table.',
  `SUM_SELECT_RANGE_CHECK` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_RANGE_CHECK column in the events_statements_current table.',
  `SUM_SELECT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_SCAN column in the events_statements_current table.',
  `SUM_SORT_MERGE_PASSES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_MERGE_PASSES column in the events_statements_current table.',
  `SUM_SORT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_RANGE column in the events_statements_current table.',
  `SUM_SORT_ROWS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_ROWS column in the events_statements_current table.',
  `SUM_SORT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_SCAN column in the events_statements_current table.',
  `SUM_NO_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the NO_INDEX_USED column in the events_statements_current table.',
  `SUM_NO_GOOD_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the NO_GOOD_INDEX_USED column in the events_statements_current table.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_statements_summary_by_host_by_event_name`
--

LOCK TABLES `events_statements_summary_by_host_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_statements_summary_by_host_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_statements_summary_by_host_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_statements_summary_by_program`
--

DROP TABLE IF EXISTS `events_statements_summary_by_program`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_statements_summary_by_program` (
  `OBJECT_TYPE` enum('EVENT','FUNCTION','PROCEDURE','TABLE','TRIGGER') DEFAULT NULL COMMENT 'Object type for which the summary is generated.',
  `OBJECT_SCHEMA` varchar(64) NOT NULL COMMENT 'The schema of the object for which the summary is generated.',
  `OBJECT_NAME` varchar(64) NOT NULL COMMENT 'The name of the object for which the summary is generated.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'The number of summarized events (from events_statements_current). This value includes all events, whether timed or nontimed.',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of the summarized timed events. This value is calculated only for timed events because nontimed events have a wait time of NULL. The same is true for the other xxx_TIMER_WAIT values.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of the summarized timed events.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of the summarized timed events.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of the summarized timed events.',
  `COUNT_STATEMENTS` bigint(20) unsigned NOT NULL COMMENT 'Total number of nested statements invoked during stored program execution.',
  `SUM_STATEMENTS_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of the summarized timed statements. This value is calculated only for timed statements because nontimed statements have a wait time of NULL. The same is true for the other xxx_STATEMENT_WAIT values.',
  `MIN_STATEMENTS_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of the summarized timed statements.',
  `AVG_STATEMENTS_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of the summarized timed statements.',
  `MAX_STATEMENTS_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of the summarized timed statements.',
  `SUM_LOCK_TIME` bigint(20) unsigned NOT NULL COMMENT 'The total time spent (in picoseconds) waiting for table locks for the summarized statements.',
  `SUM_ERRORS` bigint(20) unsigned NOT NULL COMMENT 'The total number of errors that occurend for the summarized statements.',
  `SUM_WARNINGS` bigint(20) unsigned NOT NULL COMMENT 'The total number of warnings that occurend for the summarized statements.',
  `SUM_ROWS_AFFECTED` bigint(20) unsigned NOT NULL COMMENT 'The total number of affected rows by the summarized statements.',
  `SUM_ROWS_SENT` bigint(20) unsigned NOT NULL COMMENT 'The total number of rows returned by the summarized statements.',
  `SUM_ROWS_EXAMINED` bigint(20) unsigned NOT NULL COMMENT 'The total number of rows examined by the summarized statements.',
  `SUM_CREATED_TMP_DISK_TABLES` bigint(20) unsigned NOT NULL COMMENT 'The total number of on-disk temporary tables created by the summarized statements.',
  `SUM_CREATED_TMP_TABLES` bigint(20) unsigned NOT NULL COMMENT 'The total number of in-memory temporary tables created by the summarized statements.',
  `SUM_SELECT_FULL_JOIN` bigint(20) unsigned NOT NULL COMMENT 'The total number of full joins executed by the summarized statements.',
  `SUM_SELECT_FULL_RANGE_JOIN` bigint(20) unsigned NOT NULL COMMENT 'The total number of range search joins executed by the summarized statements.',
  `SUM_SELECT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'The total number of joins that used ranges on the first table executed by the summarized statements.',
  `SUM_SELECT_RANGE_CHECK` bigint(20) unsigned NOT NULL COMMENT 'The total number of joins that check for key usage after each row executed by the summarized statements.',
  `SUM_SELECT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'The total number of joins that did a full scan of the first table executed by the summarized statements.',
  `SUM_SORT_MERGE_PASSES` bigint(20) unsigned NOT NULL COMMENT 'The total number of merge passes that the sort algorithm has had to do for the summarized statements.',
  `SUM_SORT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'The total number of sorts that were done using ranges for the summarized statements.',
  `SUM_SORT_ROWS` bigint(20) unsigned NOT NULL COMMENT 'The total number of sorted rows that were sorted by the summarized statements.',
  `SUM_SORT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'The total number of sorts that were done by scanning the table by the summarized statements.',
  `SUM_NO_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'The total number of statements that performed a table scan without using an index.',
  `SUM_NO_GOOD_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'The total number of statements where no good index was found.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_statements_summary_by_program`
--

LOCK TABLES `events_statements_summary_by_program` WRITE;
/*!40000 ALTER TABLE `events_statements_summary_by_program` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_statements_summary_by_program` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_statements_summary_by_thread_by_event_name`
--

DROP TABLE IF EXISTS `events_statements_summary_by_thread_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_statements_summary_by_thread_by_event_name` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread associated with the event. Together with EVENT_NAME uniquely identifies the row.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name. Used together with THREAD_ID for grouping events.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.',
  `SUM_LOCK_TIME` bigint(20) unsigned NOT NULL COMMENT 'Sum of the LOCK_TIME column in the events_statements_current table.',
  `SUM_ERRORS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ERRORS column in the events_statements_current table.',
  `SUM_WARNINGS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the WARNINGS column in the events_statements_current table.',
  `SUM_ROWS_AFFECTED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_AFFECTED column in the events_statements_current table.',
  `SUM_ROWS_SENT` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_SENT column in the events_statements_current table.',
  `SUM_ROWS_EXAMINED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_EXAMINED column in the events_statements_current table.',
  `SUM_CREATED_TMP_DISK_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the CREATED_TMP_DISK_TABLES column in the events_statements_current table.',
  `SUM_CREATED_TMP_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the CREATED_TMP_TABLES column in the events_statements_current table.',
  `SUM_SELECT_FULL_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_FULL_JOIN column in the events_statements_current table.',
  `SUM_SELECT_FULL_RANGE_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_FULL_RANGE_JOIN column in the events_statements_current table.',
  `SUM_SELECT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_RANGE column in the events_statements_current table.',
  `SUM_SELECT_RANGE_CHECK` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_RANGE_CHECK column in the events_statements_current table.',
  `SUM_SELECT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_SCAN column in the events_statements_current table.',
  `SUM_SORT_MERGE_PASSES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_MERGE_PASSES column in the events_statements_current table.',
  `SUM_SORT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_RANGE column in the events_statements_current table.',
  `SUM_SORT_ROWS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_ROWS column in the events_statements_current table.',
  `SUM_SORT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_SCAN column in the events_statements_current table.',
  `SUM_NO_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the NO_INDEX_USED column in the events_statements_current table.',
  `SUM_NO_GOOD_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the NO_GOOD_INDEX_USED column in the events_statements_current table.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_statements_summary_by_thread_by_event_name`
--

LOCK TABLES `events_statements_summary_by_thread_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_statements_summary_by_thread_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_statements_summary_by_thread_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_statements_summary_by_user_by_event_name`
--

DROP TABLE IF EXISTS `events_statements_summary_by_user_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_statements_summary_by_user_by_event_name` (
  `USER` char(128) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'User. Used together with EVENT_NAME for grouping events.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name. Used together with USER for grouping events.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.',
  `SUM_LOCK_TIME` bigint(20) unsigned NOT NULL COMMENT 'Sum of the LOCK_TIME column in the events_statements_current table.',
  `SUM_ERRORS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ERRORS column in the events_statements_current table.',
  `SUM_WARNINGS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the WARNINGS column in the events_statements_current table.',
  `SUM_ROWS_AFFECTED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_AFFECTED column in the events_statements_current table.',
  `SUM_ROWS_SENT` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_SENT column in the events_statements_current table.',
  `SUM_ROWS_EXAMINED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_EXAMINED column in the events_statements_current table.',
  `SUM_CREATED_TMP_DISK_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the CREATED_TMP_DISK_TABLES column in the events_statements_current table.',
  `SUM_CREATED_TMP_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the CREATED_TMP_TABLES column in the events_statements_current table.',
  `SUM_SELECT_FULL_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_FULL_JOIN column in the events_statements_current table.',
  `SUM_SELECT_FULL_RANGE_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_FULL_RANGE_JOIN column in the events_statements_current table.',
  `SUM_SELECT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_RANGE column in the events_statements_current table.',
  `SUM_SELECT_RANGE_CHECK` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_RANGE_CHECK column in the events_statements_current table.',
  `SUM_SELECT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_SCAN column in the events_statements_current table.',
  `SUM_SORT_MERGE_PASSES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_MERGE_PASSES column in the events_statements_current table.',
  `SUM_SORT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_RANGE column in the events_statements_current table.',
  `SUM_SORT_ROWS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_ROWS column in the events_statements_current table.',
  `SUM_SORT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_SCAN column in the events_statements_current table.',
  `SUM_NO_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the NO_INDEX_USED column in the events_statements_current table.',
  `SUM_NO_GOOD_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the NO_GOOD_INDEX_USED column in the events_statements_current table.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_statements_summary_by_user_by_event_name`
--

LOCK TABLES `events_statements_summary_by_user_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_statements_summary_by_user_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_statements_summary_by_user_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_statements_summary_global_by_event_name`
--

DROP TABLE IF EXISTS `events_statements_summary_global_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_statements_summary_global_by_event_name` (
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.',
  `SUM_LOCK_TIME` bigint(20) unsigned NOT NULL COMMENT 'Sum of the LOCK_TIME column in the events_statements_current table.',
  `SUM_ERRORS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ERRORS column in the events_statements_current table.',
  `SUM_WARNINGS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the WARNINGS column in the events_statements_current table.',
  `SUM_ROWS_AFFECTED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_AFFECTED column in the events_statements_current table.',
  `SUM_ROWS_SENT` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_SENT column in the events_statements_current table.',
  `SUM_ROWS_EXAMINED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the ROWS_EXAMINED column in the events_statements_current table.',
  `SUM_CREATED_TMP_DISK_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the CREATED_TMP_DISK_TABLES column in the events_statements_current table.',
  `SUM_CREATED_TMP_TABLES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the CREATED_TMP_TABLES column in the events_statements_current table.',
  `SUM_SELECT_FULL_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_FULL_JOIN column in the events_statements_current table.',
  `SUM_SELECT_FULL_RANGE_JOIN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_FULL_RANGE_JOIN column in the events_statements_current table.',
  `SUM_SELECT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_RANGE column in the events_statements_current table.',
  `SUM_SELECT_RANGE_CHECK` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_RANGE_CHECK column in the events_statements_current table.',
  `SUM_SELECT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SELECT_SCAN column in the events_statements_current table.',
  `SUM_SORT_MERGE_PASSES` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_MERGE_PASSES column in the events_statements_current table.',
  `SUM_SORT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_RANGE column in the events_statements_current table.',
  `SUM_SORT_ROWS` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_ROWS column in the events_statements_current table.',
  `SUM_SORT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'Sum of the SORT_SCAN column in the events_statements_current table.',
  `SUM_NO_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the NO_INDEX_USED column in the events_statements_current table.',
  `SUM_NO_GOOD_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'Sum of the NO_GOOD_INDEX_USED column in the events_statements_current table.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_statements_summary_global_by_event_name`
--

LOCK TABLES `events_statements_summary_global_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_statements_summary_global_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_statements_summary_global_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_transactions_current`
--

DROP TABLE IF EXISTS `events_transactions_current`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_transactions_current` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'The thread associated with the event.',
  `EVENT_ID` bigint(20) unsigned NOT NULL COMMENT 'The event id associated with the event.',
  `END_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'This column is set to NULL when the event starts and updated to the thread current event number when the event ends.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'The name of the instrument from which the event was collected. This is a NAME value from the setup_instruments table.',
  `STATE` enum('ACTIVE','COMMITTED','ROLLED BACK') DEFAULT NULL COMMENT 'The current transaction state. The value is ACTIVE (after START TRANSACTION or BEGIN), COMMITTED (after COMMIT), or ROLLED BACK (after ROLLBACK).',
  `TRX_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'Unused.',
  `GTID` varchar(64) DEFAULT NULL COMMENT 'Transaction GTID, using the format DOMAIN-SERVER_ID-SEQUENCE_NO.',
  `XID_FORMAT_ID` int(11) DEFAULT NULL COMMENT 'XA transaction format ID for GTRID and BQUAL values.',
  `XID_GTRID` varchar(130) DEFAULT NULL COMMENT 'XA global transaction ID.',
  `XID_BQUAL` varchar(130) DEFAULT NULL COMMENT 'XA transaction branch qualifier.',
  `XA_STATE` varchar(64) DEFAULT NULL COMMENT 'The state of the XA transaction. The value is ACTIVE (after XA START), IDLE (after XA END), PREPARED (after XA PREPARE), ROLLED BACK (after XA ROLLBACK), or COMMITTED (after XA COMMIT).',
  `SOURCE` varchar(64) DEFAULT NULL COMMENT 'The name of the source file containing the instrumented code that produced the event and the line number in the file at which the instrumentation occurs.',
  `TIMER_START` bigint(20) unsigned DEFAULT NULL COMMENT 'The unit is picoseconds. When event timing started. NULL if event has no timing information.',
  `TIMER_END` bigint(20) unsigned DEFAULT NULL COMMENT 'The unit is picoseconds. When event timing ended. NULL if event has no timing information.',
  `TIMER_WAIT` bigint(20) unsigned DEFAULT NULL COMMENT 'The unit is picoseconds. Event duration. NULL if event has not timing information.',
  `ACCESS_MODE` enum('READ ONLY','READ WRITE') DEFAULT NULL COMMENT 'Transaction access mode.',
  `ISOLATION_LEVEL` varchar(64) DEFAULT NULL COMMENT 'Transaction isolation level. One of: REPEATABLE READ, READ COMMITTED, READ UNCOMMITTED, or SERIALIZABLE.',
  `AUTOCOMMIT` enum('YES','NO') NOT NULL COMMENT 'Whether autcommit mode was enabled when the transaction started.',
  `NUMBER_OF_SAVEPOINTS` bigint(20) unsigned DEFAULT NULL COMMENT 'The number of SAVEPOINT statements issued during the transaction.',
  `NUMBER_OF_ROLLBACK_TO_SAVEPOINT` bigint(20) unsigned DEFAULT NULL COMMENT 'The number of ROLLBACK_TO_SAVEPOINT statements issued during the transaction.',
  `NUMBER_OF_RELEASE_SAVEPOINT` bigint(20) unsigned DEFAULT NULL COMMENT 'The number of RELEASE_SAVEPOINT statements issued during the transaction.',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned DEFAULT NULL COMMENT 'Unused.',
  `NESTING_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'The EVENT_ID value of the event within which this event is nested.',
  `NESTING_EVENT_TYPE` enum('TRANSACTION','STATEMENT','STAGE','WAIT') DEFAULT NULL COMMENT 'The nesting event type.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_transactions_current`
--

LOCK TABLES `events_transactions_current` WRITE;
/*!40000 ALTER TABLE `events_transactions_current` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_transactions_current` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_transactions_history`
--

DROP TABLE IF EXISTS `events_transactions_history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_transactions_history` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'The thread associated with the event.',
  `EVENT_ID` bigint(20) unsigned NOT NULL COMMENT 'The event id associated with the event.',
  `END_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'This column is set to NULL when the event starts and updated to the thread current event number when the event ends.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'The name of the instrument from which the event was collected. This is a NAME value from the setup_instruments table.',
  `STATE` enum('ACTIVE','COMMITTED','ROLLED BACK') DEFAULT NULL COMMENT 'The current transaction state. The value is ACTIVE (after START TRANSACTION or BEGIN), COMMITTED (after COMMIT), or ROLLED BACK (after ROLLBACK).',
  `TRX_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'Unused.',
  `GTID` varchar(64) DEFAULT NULL COMMENT 'Transaction GTID, using the format DOMAIN-SERVER_ID-SEQUENCE_NO.',
  `XID_FORMAT_ID` int(11) DEFAULT NULL COMMENT 'XA transaction format ID for GTRID and BQUAL values.',
  `XID_GTRID` varchar(130) DEFAULT NULL COMMENT 'XA global transaction ID.',
  `XID_BQUAL` varchar(130) DEFAULT NULL COMMENT 'XA transaction branch qualifier.',
  `XA_STATE` varchar(64) DEFAULT NULL COMMENT 'The state of the XA transaction. The value is ACTIVE (after XA START), IDLE (after XA END), PREPARED (after XA PREPARE), ROLLED BACK (after XA ROLLBACK), or COMMITTED (after XA COMMIT).',
  `SOURCE` varchar(64) DEFAULT NULL COMMENT 'The name of the source file containing the instrumented code that produced the event and the line number in the file at which the instrumentation occurs.',
  `TIMER_START` bigint(20) unsigned DEFAULT NULL COMMENT 'The unit is picoseconds. When event timing started. NULL if event has no timing information.',
  `TIMER_END` bigint(20) unsigned DEFAULT NULL COMMENT 'The unit is picoseconds. When event timing ended. NULL if event has no timing information.',
  `TIMER_WAIT` bigint(20) unsigned DEFAULT NULL COMMENT 'The unit is picoseconds. Event duration. NULL if event has not timing information.',
  `ACCESS_MODE` enum('READ ONLY','READ WRITE') DEFAULT NULL COMMENT 'Transaction access mode.',
  `ISOLATION_LEVEL` varchar(64) DEFAULT NULL COMMENT 'Transaction isolation level. One of: REPEATABLE READ, READ COMMITTED, READ UNCOMMITTED, or SERIALIZABLE.',
  `AUTOCOMMIT` enum('YES','NO') NOT NULL COMMENT 'Whether autcommit mode was enabled when the transaction started.',
  `NUMBER_OF_SAVEPOINTS` bigint(20) unsigned DEFAULT NULL COMMENT 'The number of SAVEPOINT statements issued during the transaction.',
  `NUMBER_OF_ROLLBACK_TO_SAVEPOINT` bigint(20) unsigned DEFAULT NULL COMMENT 'The number of ROLLBACK_TO_SAVEPOINT statements issued during the transaction.',
  `NUMBER_OF_RELEASE_SAVEPOINT` bigint(20) unsigned DEFAULT NULL COMMENT 'The number of RELEASE_SAVEPOINT statements issued during the transaction.',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned DEFAULT NULL COMMENT 'Unused.',
  `NESTING_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'The EVENT_ID value of the event within which this event is nested.',
  `NESTING_EVENT_TYPE` enum('TRANSACTION','STATEMENT','STAGE','WAIT') DEFAULT NULL COMMENT 'The nesting event type.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_transactions_history`
--

LOCK TABLES `events_transactions_history` WRITE;
/*!40000 ALTER TABLE `events_transactions_history` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_transactions_history` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_transactions_history_long`
--

DROP TABLE IF EXISTS `events_transactions_history_long`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_transactions_history_long` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'The thread associated with the event.',
  `EVENT_ID` bigint(20) unsigned NOT NULL COMMENT 'The event id associated with the event.',
  `END_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'This column is set to NULL when the event starts and updated to the thread current event number when the event ends.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'The name of the instrument from which the event was collected. This is a NAME value from the setup_instruments table.',
  `STATE` enum('ACTIVE','COMMITTED','ROLLED BACK') DEFAULT NULL COMMENT 'The current transaction state. The value is ACTIVE (after START TRANSACTION or BEGIN), COMMITTED (after COMMIT), or ROLLED BACK (after ROLLBACK).',
  `TRX_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'Unused.',
  `GTID` varchar(64) DEFAULT NULL COMMENT 'Transaction GTID, using the format DOMAIN-SERVER_ID-SEQUENCE_NO.',
  `XID_FORMAT_ID` int(11) DEFAULT NULL COMMENT 'XA transaction format ID for GTRID and BQUAL values.',
  `XID_GTRID` varchar(130) DEFAULT NULL COMMENT 'XA global transaction ID.',
  `XID_BQUAL` varchar(130) DEFAULT NULL COMMENT 'XA transaction branch qualifier.',
  `XA_STATE` varchar(64) DEFAULT NULL COMMENT 'The state of the XA transaction. The value is ACTIVE (after XA START), IDLE (after XA END), PREPARED (after XA PREPARE), ROLLED BACK (after XA ROLLBACK), or COMMITTED (after XA COMMIT).',
  `SOURCE` varchar(64) DEFAULT NULL COMMENT 'The name of the source file containing the instrumented code that produced the event and the line number in the file at which the instrumentation occurs.',
  `TIMER_START` bigint(20) unsigned DEFAULT NULL COMMENT 'The unit is picoseconds. When event timing started. NULL if event has no timing information.',
  `TIMER_END` bigint(20) unsigned DEFAULT NULL COMMENT 'The unit is picoseconds. When event timing ended. NULL if event has no timing information.',
  `TIMER_WAIT` bigint(20) unsigned DEFAULT NULL COMMENT 'The unit is picoseconds. Event duration. NULL if event has not timing information.',
  `ACCESS_MODE` enum('READ ONLY','READ WRITE') DEFAULT NULL COMMENT 'Transaction access mode.',
  `ISOLATION_LEVEL` varchar(64) DEFAULT NULL COMMENT 'Transaction isolation level. One of: REPEATABLE READ, READ COMMITTED, READ UNCOMMITTED, or SERIALIZABLE.',
  `AUTOCOMMIT` enum('YES','NO') NOT NULL COMMENT 'Whether autcommit mode was enabled when the transaction started.',
  `NUMBER_OF_SAVEPOINTS` bigint(20) unsigned DEFAULT NULL COMMENT 'The number of SAVEPOINT statements issued during the transaction.',
  `NUMBER_OF_ROLLBACK_TO_SAVEPOINT` bigint(20) unsigned DEFAULT NULL COMMENT 'The number of ROLLBACK_TO_SAVEPOINT statements issued during the transaction.',
  `NUMBER_OF_RELEASE_SAVEPOINT` bigint(20) unsigned DEFAULT NULL COMMENT 'The number of RELEASE_SAVEPOINT statements issued during the transaction.',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned DEFAULT NULL COMMENT 'Unused.',
  `NESTING_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'The EVENT_ID value of the event within which this event is nested.',
  `NESTING_EVENT_TYPE` enum('TRANSACTION','STATEMENT','STAGE','WAIT') DEFAULT NULL COMMENT 'The nesting event type.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_transactions_history_long`
--

LOCK TABLES `events_transactions_history_long` WRITE;
/*!40000 ALTER TABLE `events_transactions_history_long` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_transactions_history_long` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_transactions_summary_by_account_by_event_name`
--

DROP TABLE IF EXISTS `events_transactions_summary_by_account_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_transactions_summary_by_account_by_event_name` (
  `USER` char(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'User for which summary is generated.',
  `HOST` char(60) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'Host for which summary is generated.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name for which summary is generated.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'The number of summarized events. This value includes all events, whether timed or nontimed.',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of the summarized timed events. This value is calculated only for timed events because nontimed events have a wait time of NULL. The same is true for the other xxx_TIMER_WAIT values.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of the summarized timed events.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of the summarized timed events.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of the summarized timed events.',
  `COUNT_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The total number of only READ/WRITE transaction events.',
  `SUM_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of only READ/WRITE transaction events.',
  `MIN_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of only READ/WRITE transaction events.',
  `AVG_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of only READ/WRITE transaction events.',
  `MAX_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of only READ/WRITE transaction events.',
  `COUNT_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The total number of only READ ONLY transaction events.',
  `SUM_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of only READ ONLY transaction events.',
  `MIN_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of only READ ONLY transaction events.',
  `AVG_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of only READ ONLY transaction events.',
  `MAX_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of only READ ONLY transaction events.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_transactions_summary_by_account_by_event_name`
--

LOCK TABLES `events_transactions_summary_by_account_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_transactions_summary_by_account_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_transactions_summary_by_account_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_transactions_summary_by_host_by_event_name`
--

DROP TABLE IF EXISTS `events_transactions_summary_by_host_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_transactions_summary_by_host_by_event_name` (
  `HOST` char(60) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'Host for which summary is generated.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name for which summary is generated.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'The number of summarized events. This value includes all events, whether timed or nontimed.',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of the summarized timed events. This value is calculated only for timed events because nontimed events have a wait time of NULL. The same is true for the other xxx_TIMER_WAIT values.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of the summarized timed events.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of the summarized timed events.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of the summarized timed events.',
  `COUNT_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The total number of only READ/WRITE transaction events.',
  `SUM_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of only READ/WRITE transaction events.',
  `MIN_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of only READ/WRITE transaction events.',
  `AVG_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of only READ/WRITE transaction events.',
  `MAX_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of only READ/WRITE transaction events.',
  `COUNT_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The total number of only READ ONLY transaction events.',
  `SUM_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of only READ ONLY transaction events.',
  `MIN_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of only READ ONLY transaction events.',
  `AVG_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of only READ ONLY transaction events.',
  `MAX_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of only READ ONLY transaction events.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_transactions_summary_by_host_by_event_name`
--

LOCK TABLES `events_transactions_summary_by_host_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_transactions_summary_by_host_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_transactions_summary_by_host_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_transactions_summary_by_thread_by_event_name`
--

DROP TABLE IF EXISTS `events_transactions_summary_by_thread_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_transactions_summary_by_thread_by_event_name` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread for which summary is generated.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name for which summary is generated.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'The number of summarized events. This value includes all events, whether timed or nontimed.',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of the summarized timed events. This value is calculated only for timed events because nontimed events have a wait time of NULL. The same is true for the other xxx_TIMER_WAIT values.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of the summarized timed events.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of the summarized timed events.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of the summarized timed events.',
  `COUNT_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The total number of only READ/WRITE transaction events.',
  `SUM_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of only READ/WRITE transaction events.',
  `MIN_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of only READ/WRITE transaction events.',
  `AVG_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of only READ/WRITE transaction events.',
  `MAX_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of only READ/WRITE transaction events.',
  `COUNT_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The total number of only READ ONLY transaction events.',
  `SUM_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of only READ ONLY transaction events.',
  `MIN_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of only READ ONLY transaction events.',
  `AVG_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of only READ ONLY transaction events.',
  `MAX_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of only READ ONLY transaction events.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_transactions_summary_by_thread_by_event_name`
--

LOCK TABLES `events_transactions_summary_by_thread_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_transactions_summary_by_thread_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_transactions_summary_by_thread_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_transactions_summary_by_user_by_event_name`
--

DROP TABLE IF EXISTS `events_transactions_summary_by_user_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_transactions_summary_by_user_by_event_name` (
  `USER` char(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'User for which summary is generated.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name for which summary is generated.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'The number of summarized events. This value includes all events, whether timed or nontimed.',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of the summarized timed events. This value is calculated only for timed events because nontimed events have a wait time of NULL. The same is true for the other xxx_TIMER_WAIT values.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of the summarized timed events.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of the summarized timed events.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of the summarized timed events.',
  `COUNT_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The total number of only READ/WRITE transaction events.',
  `SUM_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of only READ/WRITE transaction events.',
  `MIN_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of only READ/WRITE transaction events.',
  `AVG_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of only READ/WRITE transaction events.',
  `MAX_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of only READ/WRITE transaction events.',
  `COUNT_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The total number of only READ ONLY transaction events.',
  `SUM_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of only READ ONLY transaction events.',
  `MIN_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of only READ ONLY transaction events.',
  `AVG_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of only READ ONLY transaction events.',
  `MAX_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of only READ ONLY transaction events.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_transactions_summary_by_user_by_event_name`
--

LOCK TABLES `events_transactions_summary_by_user_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_transactions_summary_by_user_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_transactions_summary_by_user_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_transactions_summary_global_by_event_name`
--

DROP TABLE IF EXISTS `events_transactions_summary_global_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_transactions_summary_global_by_event_name` (
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name for which summary is generated.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'The number of summarized events. This value includes all events, whether timed or nontimed.',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of the summarized timed events. This value is calculated only for timed events because nontimed events have a wait time of NULL. The same is true for the other xxx_TIMER_WAIT values.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of the summarized timed events.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of the summarized timed events.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of the summarized timed events.',
  `COUNT_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The total number of only READ/WRITE transaction events.',
  `SUM_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of only READ/WRITE transaction events.',
  `MIN_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of only READ/WRITE transaction events.',
  `AVG_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of only READ/WRITE transaction events.',
  `MAX_TIMER_READ_WRITE` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of only READ/WRITE transaction events.',
  `COUNT_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The total number of only READ ONLY transaction events.',
  `SUM_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The total wait time of only READ ONLY transaction events.',
  `MIN_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The minimum wait time of only READ ONLY transaction events.',
  `AVG_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The average wait time of only READ ONLY transaction events.',
  `MAX_TIMER_READ_ONLY` bigint(20) unsigned NOT NULL COMMENT 'The maximum wait time of only READ ONLY transaction events.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_transactions_summary_global_by_event_name`
--

LOCK TABLES `events_transactions_summary_global_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_transactions_summary_global_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_transactions_summary_global_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_waits_current`
--

DROP TABLE IF EXISTS `events_waits_current`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_waits_current` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread associated with the event. Together with EVENT_ID uniquely identifies the row.',
  `EVENT_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread''s current event number at the start of the event. Together with THREAD_ID uniquely identifies the row.',
  `END_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'NULL when the event starts, set to the thread''s current event number at the end of the event.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event instrument name and a NAME from the setup_instruments table',
  `SOURCE` varchar(64) DEFAULT NULL COMMENT 'Name and line number of the source file containing the instrumented code that produced the event.',
  `TIMER_START` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing started or NULL if timing is not collected.',
  `TIMER_END` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing ended, or NULL if the event has not ended or timing is not collected.',
  `TIMER_WAIT` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds of the event''s duration or NULL if the event has not ended or timing is not collected.',
  `SPINS` int(10) unsigned DEFAULT NULL COMMENT 'Number of spin rounds for a mutex, or NULL if spin rounds are not used, or spinning is not instrumented.',
  `OBJECT_SCHEMA` varchar(64) DEFAULT NULL COMMENT 'Name of the schema that contains the table for table I/O objects, otherwise NULL for file I/O and synchronization objects.',
  `OBJECT_NAME` varchar(512) DEFAULT NULL COMMENT 'File name for file I/O objects, table name for table I/O objects, the socket''s IP:PORT value for a socket object or NULL for a synchronization object.',
  `INDEX_NAME` varchar(64) DEFAULT NULL COMMENT 'Name of the index, PRIMARY for the primary key, or NULL for no index used.',
  `OBJECT_TYPE` varchar(64) DEFAULT NULL COMMENT 'FILE for a file object, TABLE or TEMPORARY TABLE for a table object, or NULL for a synchronization object.',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned NOT NULL COMMENT 'Address in memory of the object.',
  `NESTING_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'EVENT_ID of event within which this event nests.',
  `NESTING_EVENT_TYPE` enum('TRANSACTION','STATEMENT','STAGE','WAIT') DEFAULT NULL COMMENT 'Nesting event type. Either statement, stage or wait.',
  `OPERATION` varchar(32) NOT NULL COMMENT 'Operation type, for example read, write or lock',
  `NUMBER_OF_BYTES` bigint(20) DEFAULT NULL COMMENT 'Number of bytes that the operation read or wrote, or NULL for table I/O waits.',
  `FLAGS` int(10) unsigned DEFAULT NULL COMMENT 'Reserved for use in the future.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_waits_current`
--

LOCK TABLES `events_waits_current` WRITE;
/*!40000 ALTER TABLE `events_waits_current` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_waits_current` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_waits_history`
--

DROP TABLE IF EXISTS `events_waits_history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_waits_history` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread associated with the event. Together with EVENT_ID uniquely identifies the row.',
  `EVENT_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread''s current event number at the start of the event. Together with THREAD_ID uniquely identifies the row.',
  `END_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'NULL when the event starts, set to the thread''s current event number at the end of the event.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event instrument name and a NAME from the setup_instruments table',
  `SOURCE` varchar(64) DEFAULT NULL COMMENT 'Name and line number of the source file containing the instrumented code that produced the event.',
  `TIMER_START` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing started or NULL if timing is not collected.',
  `TIMER_END` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing ended, or NULL if the event has not ended or timing is not collected.',
  `TIMER_WAIT` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds of the event''s duration or NULL if the event has not ended or timing is not collected.',
  `SPINS` int(10) unsigned DEFAULT NULL COMMENT 'Number of spin rounds for a mutex, or NULL if spin rounds are not used, or spinning is not instrumented.',
  `OBJECT_SCHEMA` varchar(64) DEFAULT NULL COMMENT 'Name of the schema that contains the table for table I/O objects, otherwise NULL for file I/O and synchronization objects.',
  `OBJECT_NAME` varchar(512) DEFAULT NULL COMMENT 'File name for file I/O objects, table name for table I/O objects, the socket''s IP:PORT value for a socket object or NULL for a synchronization object.',
  `INDEX_NAME` varchar(64) DEFAULT NULL COMMENT 'Name of the index, PRIMARY for the primary key, or NULL for no index used.',
  `OBJECT_TYPE` varchar(64) DEFAULT NULL COMMENT 'FILE for a file object, TABLE or TEMPORARY TABLE for a table object, or NULL for a synchronization object.',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned NOT NULL COMMENT 'Address in memory of the object.',
  `NESTING_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'EVENT_ID of event within which this event nests.',
  `NESTING_EVENT_TYPE` enum('TRANSACTION','STATEMENT','STAGE','WAIT') DEFAULT NULL COMMENT 'Nesting event type. Either statement, stage or wait.',
  `OPERATION` varchar(32) NOT NULL COMMENT 'Operation type, for example read, write or lock',
  `NUMBER_OF_BYTES` bigint(20) DEFAULT NULL COMMENT 'Number of bytes that the operation read or wrote, or NULL for table I/O waits.',
  `FLAGS` int(10) unsigned DEFAULT NULL COMMENT 'Reserved for use in the future.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_waits_history`
--

LOCK TABLES `events_waits_history` WRITE;
/*!40000 ALTER TABLE `events_waits_history` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_waits_history` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_waits_history_long`
--

DROP TABLE IF EXISTS `events_waits_history_long`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_waits_history_long` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread associated with the event. Together with EVENT_ID uniquely identifies the row.',
  `EVENT_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread''s current event number at the start of the event. Together with THREAD_ID uniquely identifies the row.',
  `END_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'NULL when the event starts, set to the thread''s current event number at the end of the event.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event instrument name and a NAME from the setup_instruments table',
  `SOURCE` varchar(64) DEFAULT NULL COMMENT 'Name and line number of the source file containing the instrumented code that produced the event.',
  `TIMER_START` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing started or NULL if timing is not collected.',
  `TIMER_END` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds when the event timing ended, or NULL if the event has not ended or timing is not collected.',
  `TIMER_WAIT` bigint(20) unsigned DEFAULT NULL COMMENT 'Value in picoseconds of the event''s duration or NULL if the event has not ended or timing is not collected.',
  `SPINS` int(10) unsigned DEFAULT NULL COMMENT 'Number of spin rounds for a mutex, or NULL if spin rounds are not used, or spinning is not instrumented.',
  `OBJECT_SCHEMA` varchar(64) DEFAULT NULL COMMENT 'Name of the schema that contains the table for table I/O objects, otherwise NULL for file I/O and synchronization objects.',
  `OBJECT_NAME` varchar(512) DEFAULT NULL COMMENT 'File name for file I/O objects, table name for table I/O objects, the socket''s IP:PORT value for a socket object or NULL for a synchronization object.',
  `INDEX_NAME` varchar(64) DEFAULT NULL COMMENT 'Name of the index, PRIMARY for the primary key, or NULL for no index used.',
  `OBJECT_TYPE` varchar(64) DEFAULT NULL COMMENT 'FILE for a file object, TABLE or TEMPORARY TABLE for a table object, or NULL for a synchronization object.',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned NOT NULL COMMENT 'Address in memory of the object.',
  `NESTING_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'EVENT_ID of event within which this event nests.',
  `NESTING_EVENT_TYPE` enum('TRANSACTION','STATEMENT','STAGE','WAIT') DEFAULT NULL COMMENT 'Nesting event type. Either statement, stage or wait.',
  `OPERATION` varchar(32) NOT NULL COMMENT 'Operation type, for example read, write or lock',
  `NUMBER_OF_BYTES` bigint(20) DEFAULT NULL COMMENT 'Number of bytes that the operation read or wrote, or NULL for table I/O waits.',
  `FLAGS` int(10) unsigned DEFAULT NULL COMMENT 'Reserved for use in the future.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_waits_history_long`
--

LOCK TABLES `events_waits_history_long` WRITE;
/*!40000 ALTER TABLE `events_waits_history_long` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_waits_history_long` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_waits_summary_by_account_by_event_name`
--

DROP TABLE IF EXISTS `events_waits_summary_by_account_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_waits_summary_by_account_by_event_name` (
  `USER` char(128) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'User. Used together with HOST and EVENT_NAME for grouping events.',
  `HOST` char(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'Host. Used together with USER and EVENT_NAME for grouping events.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name. Used together with USER and HOST for grouping events.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_waits_summary_by_account_by_event_name`
--

LOCK TABLES `events_waits_summary_by_account_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_waits_summary_by_account_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_waits_summary_by_account_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_waits_summary_by_host_by_event_name`
--

DROP TABLE IF EXISTS `events_waits_summary_by_host_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_waits_summary_by_host_by_event_name` (
  `HOST` char(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'Host. Used together with EVENT_NAME for grouping events.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name. Used together with USER and HOST for grouping events.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_waits_summary_by_host_by_event_name`
--

LOCK TABLES `events_waits_summary_by_host_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_waits_summary_by_host_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_waits_summary_by_host_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_waits_summary_by_instance`
--

DROP TABLE IF EXISTS `events_waits_summary_by_instance`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_waits_summary_by_instance` (
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name. Used together with OBJECT_INSTANCE_BEGIN for grouping events.',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned NOT NULL COMMENT 'If an instrument creates multiple instances, each instance has a unique OBJECT_INSTANCE_BEGIN value to allow for grouping by instance.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_waits_summary_by_instance`
--

LOCK TABLES `events_waits_summary_by_instance` WRITE;
/*!40000 ALTER TABLE `events_waits_summary_by_instance` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_waits_summary_by_instance` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_waits_summary_by_thread_by_event_name`
--

DROP TABLE IF EXISTS `events_waits_summary_by_thread_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_waits_summary_by_thread_by_event_name` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread associated with the event. Together with EVENT_NAME uniquely identifies the row.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name. Used together with THREAD_ID for grouping events.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_waits_summary_by_thread_by_event_name`
--

LOCK TABLES `events_waits_summary_by_thread_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_waits_summary_by_thread_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_waits_summary_by_thread_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_waits_summary_by_user_by_event_name`
--

DROP TABLE IF EXISTS `events_waits_summary_by_user_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_waits_summary_by_user_by_event_name` (
  `USER` char(128) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'User. Used together with EVENT_NAME for grouping events.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name. Used together with USER for grouping events.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_waits_summary_by_user_by_event_name`
--

LOCK TABLES `events_waits_summary_by_user_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_waits_summary_by_user_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_waits_summary_by_user_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `events_waits_summary_global_by_event_name`
--

DROP TABLE IF EXISTS `events_waits_summary_global_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `events_waits_summary_global_by_event_name` (
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events_waits_summary_global_by_event_name`
--

LOCK TABLES `events_waits_summary_global_by_event_name` WRITE;
/*!40000 ALTER TABLE `events_waits_summary_global_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `events_waits_summary_global_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `file_instances`
--

DROP TABLE IF EXISTS `file_instances`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `file_instances` (
  `FILE_NAME` varchar(512) NOT NULL COMMENT 'File name.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Instrument name associated with the file.',
  `OPEN_COUNT` int(10) unsigned NOT NULL COMMENT 'Open handles on the file. A value of greater than zero means that the file is currently open.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `file_instances`
--

LOCK TABLES `file_instances` WRITE;
/*!40000 ALTER TABLE `file_instances` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `file_instances` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `file_summary_by_event_name`
--

DROP TABLE IF EXISTS `file_summary_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `file_summary_by_event_name` (
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.',
  `COUNT_READ` bigint(20) unsigned NOT NULL COMMENT 'Number of all read operations, including FGETS, FGETC, FREAD, and READ.',
  `SUM_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all read operations that are timed.',
  `MIN_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all read operations that are timed.',
  `AVG_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all read operations that are timed.',
  `MAX_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all read operations that are timed.',
  `SUM_NUMBER_OF_BYTES_READ` bigint(20) NOT NULL COMMENT 'Bytes read by read operations.',
  `COUNT_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Number of all write operations, including FPUTS, FPUTC, FPRINTF, VFPRINTF, FWRITE, and PWRITE.',
  `SUM_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all write operations that are timed.',
  `MIN_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all write operations that are timed.',
  `AVG_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all write operations that are timed.',
  `MAX_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all write operations that are timed.',
  `SUM_NUMBER_OF_BYTES_WRITE` bigint(20) NOT NULL COMMENT 'Bytes written by write operations.',
  `COUNT_MISC` bigint(20) unsigned NOT NULL COMMENT 'Number of all miscellaneous operations not counted above, including CREATE, DELETE, OPEN, CLOSE, STREAM_OPEN, STREAM_CLOSE, SEEK, TELL, FLUSH, STAT, FSTAT, CHSIZE, RENAME, and SYNC.',
  `SUM_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all miscellaneous operations that are timed.',
  `MIN_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all miscellaneous operations that are timed.',
  `AVG_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all miscellaneous operations that are timed.',
  `MAX_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all miscellaneous operations that are timed.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `file_summary_by_event_name`
--

LOCK TABLES `file_summary_by_event_name` WRITE;
/*!40000 ALTER TABLE `file_summary_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `file_summary_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `file_summary_by_instance`
--

DROP TABLE IF EXISTS `file_summary_by_instance`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `file_summary_by_instance` (
  `FILE_NAME` varchar(512) NOT NULL COMMENT 'File name.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name.',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned NOT NULL COMMENT 'Address in memory. Together with FILE_NAME and EVENT_NAME uniquely identifies a row.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.',
  `COUNT_READ` bigint(20) unsigned NOT NULL COMMENT 'Number of all read operations, including FGETS, FGETC, FREAD, and READ.',
  `SUM_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all read operations that are timed.',
  `MIN_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all read operations that are timed.',
  `AVG_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all read operations that are timed.',
  `MAX_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all read operations that are timed.',
  `SUM_NUMBER_OF_BYTES_READ` bigint(20) NOT NULL COMMENT 'Bytes read by read operations.',
  `COUNT_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Number of all write operations, including FPUTS, FPUTC, FPRINTF, VFPRINTF, FWRITE, and PWRITE.',
  `SUM_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all write operations that are timed.',
  `MIN_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all write operations that are timed.',
  `AVG_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all write operations that are timed.',
  `MAX_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all write operations that are timed.',
  `SUM_NUMBER_OF_BYTES_WRITE` bigint(20) NOT NULL COMMENT 'Bytes written by write operations.',
  `COUNT_MISC` bigint(20) unsigned NOT NULL COMMENT 'Number of all miscellaneous operations not counted above, including CREATE, DELETE, OPEN, CLOSE, STREAM_OPEN, STREAM_CLOSE, SEEK, TELL, FLUSH, STAT, FSTAT, CHSIZE, RENAME, and SYNC.',
  `SUM_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all miscellaneous operations that are timed.',
  `MIN_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all miscellaneous operations that are timed.',
  `AVG_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all miscellaneous operations that are timed.',
  `MAX_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all miscellaneous operations that are timed.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `file_summary_by_instance`
--

LOCK TABLES `file_summary_by_instance` WRITE;
/*!40000 ALTER TABLE `file_summary_by_instance` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `file_summary_by_instance` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `global_status`
--

DROP TABLE IF EXISTS `global_status`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `global_status` (
  `VARIABLE_NAME` varchar(64) NOT NULL COMMENT 'The global status variable name.',
  `VARIABLE_VALUE` varchar(1024) DEFAULT NULL COMMENT 'The global status variable value.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `global_status`
--

LOCK TABLES `global_status` WRITE;
/*!40000 ALTER TABLE `global_status` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `global_status` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `host_cache`
--

DROP TABLE IF EXISTS `host_cache`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `host_cache` (
  `IP` varchar(64) NOT NULL COMMENT 'Client IP address.',
  `HOST` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'IP''s resolved DNS host name, or NULL if unknown.',
  `HOST_VALIDATED` enum('YES','NO') NOT NULL COMMENT 'YES if the IP-to-host DNS lookup was successful, and the HOST column can be used to avoid DNS calls, or NO if unsuccessful, in which case DNS lookup is performed for each connect until either successful or a permanent error.',
  `SUM_CONNECT_ERRORS` bigint(20) NOT NULL COMMENT 'Number of connection errors. Counts only protocol handshake errors for hosts that passed validation. These errors count towards max_connect_errors.',
  `COUNT_HOST_BLOCKED_ERRORS` bigint(20) NOT NULL COMMENT 'Number of blocked connections because SUM_CONNECT_ERRORS exceeded the max_connect_errors system variable.',
  `COUNT_NAMEINFO_TRANSIENT_ERRORS` bigint(20) NOT NULL COMMENT 'Number of transient errors during IP-to-host DNS lookups.',
  `COUNT_NAMEINFO_PERMANENT_ERRORS` bigint(20) NOT NULL COMMENT 'Number of permanent errors during IP-to-host DNS lookups.',
  `COUNT_FORMAT_ERRORS` bigint(20) NOT NULL COMMENT 'Number of host name format errors, for example a numeric host column.',
  `COUNT_ADDRINFO_TRANSIENT_ERRORS` bigint(20) NOT NULL COMMENT 'Number of transient errors during host-to-IP reverse DNS lookups.',
  `COUNT_ADDRINFO_PERMANENT_ERRORS` bigint(20) NOT NULL COMMENT 'Number of permanent errors during host-to-IP reverse DNS lookups.',
  `COUNT_FCRDNS_ERRORS` bigint(20) NOT NULL COMMENT 'Number of forward-confirmed reverse DNS errors, which occur when IP-to-host DNS lookup does not match the originating IP address.',
  `COUNT_HOST_ACL_ERRORS` bigint(20) NOT NULL COMMENT 'Number of errors occurring because no user from the host is permitted to log in. These attempts return error code 1130 ER_HOST_NOT_PRIVILEGED and do not proceed to username and password authentication.',
  `COUNT_NO_AUTH_PLUGIN_ERRORS` bigint(20) NOT NULL COMMENT 'Number of errors due to requesting an authentication plugin that was not available. This can be due to the plugin never having been loaded, or the load attempt failing.',
  `COUNT_AUTH_PLUGIN_ERRORS` bigint(20) NOT NULL COMMENT 'Number of errors reported by an authentication plugin. Plugins can increment COUNT_AUTHENTICATION_ERRORS or COUNT_HANDSHAKE_ERRORS instead, but, if specified or the error is unknown, this column is incremented.',
  `COUNT_HANDSHAKE_ERRORS` bigint(20) NOT NULL COMMENT 'Number of errors detected at the wire protocol level.',
  `COUNT_PROXY_USER_ERRORS` bigint(20) NOT NULL COMMENT 'Number of errors detected when a proxy user is proxied to a user that does not exist.',
  `COUNT_PROXY_USER_ACL_ERRORS` bigint(20) NOT NULL COMMENT 'Number of errors detected when a proxy user is proxied to a user that exists, but the proxy user doesn''t have the PROXY privilege.',
  `COUNT_AUTHENTICATION_ERRORS` bigint(20) NOT NULL COMMENT 'Number of errors where authentication failed.',
  `COUNT_SSL_ERRORS` bigint(20) NOT NULL COMMENT 'Number of errors due to TLS problems.',
  `COUNT_MAX_USER_CONNECTIONS_ERRORS` bigint(20) NOT NULL COMMENT 'Number of errors due to the per-user quota being exceeded.',
  `COUNT_MAX_USER_CONNECTIONS_PER_HOUR_ERRORS` bigint(20) NOT NULL COMMENT 'Number of errors due to the per-hour quota being exceeded.',
  `COUNT_DEFAULT_DATABASE_ERRORS` bigint(20) NOT NULL COMMENT 'Number of errors due to the user not having permission to access the specified default database, or it not existing.',
  `COUNT_INIT_CONNECT_ERRORS` bigint(20) NOT NULL COMMENT 'Number of errors due to statements in the init_connect system variable.',
  `COUNT_LOCAL_ERRORS` bigint(20) NOT NULL COMMENT 'Number of local server errors, such as out-of-memory errors, unrelated to network, authentication, or authorization.',
  `COUNT_UNKNOWN_ERRORS` bigint(20) NOT NULL COMMENT 'Number of unknown errors that cannot be allocated to another column.',
  `FIRST_SEEN` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'Timestamp of the first connection attempt by the IP.',
  `LAST_SEEN` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'Timestamp of the most recent connection attempt by the IP.',
  `FIRST_ERROR_SEEN` timestamp NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'Timestamp of the first error seen from the IP.',
  `LAST_ERROR_SEEN` timestamp NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'Timestamp of the most recent error seen from the IP.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `host_cache`
--

LOCK TABLES `host_cache` WRITE;
/*!40000 ALTER TABLE `host_cache` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `host_cache` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `hosts`
--

DROP TABLE IF EXISTS `hosts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `hosts` (
  `HOST` char(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'Host name used by the client to connect, NULL for internal threads or user sessions that failed to authenticate.',
  `CURRENT_CONNECTIONS` bigint(20) NOT NULL COMMENT 'Current number of the host''s connections.',
  `TOTAL_CONNECTIONS` bigint(20) NOT NULL COMMENT 'Total number of the host''s connections'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `hosts`
--

LOCK TABLES `hosts` WRITE;
/*!40000 ALTER TABLE `hosts` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `hosts` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `memory_summary_by_account_by_event_name`
--

DROP TABLE IF EXISTS `memory_summary_by_account_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `memory_summary_by_account_by_event_name` (
  `USER` char(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'User portion of the account.',
  `HOST` char(60) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'Host portion of the account.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name.',
  `COUNT_ALLOC` bigint(20) unsigned NOT NULL COMMENT 'Total number of allocations to memory.',
  `COUNT_FREE` bigint(20) unsigned NOT NULL COMMENT 'Total number of attempts to free the allocated memory.',
  `SUM_NUMBER_OF_BYTES_ALLOC` bigint(20) unsigned NOT NULL COMMENT 'Total number of bytes allocated.',
  `SUM_NUMBER_OF_BYTES_FREE` bigint(20) unsigned NOT NULL COMMENT 'Total number of bytes freed',
  `LOW_COUNT_USED` bigint(20) NOT NULL COMMENT 'Lowest number of allocated blocks (lowest value of CURRENT_COUNT_USED).',
  `CURRENT_COUNT_USED` bigint(20) NOT NULL COMMENT 'Currently allocated blocks that have not been freed (COUNT_ALLOC minus COUNT_FREE).',
  `HIGH_COUNT_USED` bigint(20) NOT NULL COMMENT 'Highest number of allocated blocks (highest value of CURRENT_COUNT_USED).',
  `LOW_NUMBER_OF_BYTES_USED` bigint(20) NOT NULL COMMENT 'Lowest number of bytes used.',
  `CURRENT_NUMBER_OF_BYTES_USED` bigint(20) NOT NULL COMMENT 'Current number of bytes used (total allocated minus total freed).',
  `HIGH_NUMBER_OF_BYTES_USED` bigint(20) NOT NULL COMMENT 'Highest number of bytes used.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `memory_summary_by_account_by_event_name`
--

LOCK TABLES `memory_summary_by_account_by_event_name` WRITE;
/*!40000 ALTER TABLE `memory_summary_by_account_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `memory_summary_by_account_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `memory_summary_by_host_by_event_name`
--

DROP TABLE IF EXISTS `memory_summary_by_host_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `memory_summary_by_host_by_event_name` (
  `HOST` char(60) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'Host portion of the account.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name.',
  `COUNT_ALLOC` bigint(20) unsigned NOT NULL COMMENT 'Total number of allocations to memory.',
  `COUNT_FREE` bigint(20) unsigned NOT NULL COMMENT 'Total number of attempts to free the allocated memory.',
  `SUM_NUMBER_OF_BYTES_ALLOC` bigint(20) unsigned NOT NULL COMMENT 'Total number of bytes allocated.',
  `SUM_NUMBER_OF_BYTES_FREE` bigint(20) unsigned NOT NULL COMMENT 'Total number of bytes freed',
  `LOW_COUNT_USED` bigint(20) NOT NULL COMMENT 'Lowest number of allocated blocks (lowest value of CURRENT_COUNT_USED).',
  `CURRENT_COUNT_USED` bigint(20) NOT NULL COMMENT 'Currently allocated blocks that have not been freed (COUNT_ALLOC minus COUNT_FREE).',
  `HIGH_COUNT_USED` bigint(20) NOT NULL COMMENT 'Highest number of allocated blocks (highest value of CURRENT_COUNT_USED).',
  `LOW_NUMBER_OF_BYTES_USED` bigint(20) NOT NULL COMMENT 'Lowest number of bytes used.',
  `CURRENT_NUMBER_OF_BYTES_USED` bigint(20) NOT NULL COMMENT 'Current number of bytes used (total allocated minus total freed).',
  `HIGH_NUMBER_OF_BYTES_USED` bigint(20) NOT NULL COMMENT 'Highest number of bytes used.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `memory_summary_by_host_by_event_name`
--

LOCK TABLES `memory_summary_by_host_by_event_name` WRITE;
/*!40000 ALTER TABLE `memory_summary_by_host_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `memory_summary_by_host_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `memory_summary_by_thread_by_event_name`
--

DROP TABLE IF EXISTS `memory_summary_by_thread_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `memory_summary_by_thread_by_event_name` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'Thread id.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name.',
  `COUNT_ALLOC` bigint(20) unsigned NOT NULL COMMENT 'Total number of allocations to memory.',
  `COUNT_FREE` bigint(20) unsigned NOT NULL COMMENT 'Total number of attempts to free the allocated memory.',
  `SUM_NUMBER_OF_BYTES_ALLOC` bigint(20) unsigned NOT NULL COMMENT 'Total number of bytes allocated.',
  `SUM_NUMBER_OF_BYTES_FREE` bigint(20) unsigned NOT NULL COMMENT 'Total number of bytes freed',
  `LOW_COUNT_USED` bigint(20) NOT NULL COMMENT 'Lowest number of allocated blocks (lowest value of CURRENT_COUNT_USED).',
  `CURRENT_COUNT_USED` bigint(20) NOT NULL COMMENT 'Currently allocated blocks that have not been freed (COUNT_ALLOC minus COUNT_FREE).',
  `HIGH_COUNT_USED` bigint(20) NOT NULL COMMENT 'Highest number of allocated blocks (highest value of CURRENT_COUNT_USED).',
  `LOW_NUMBER_OF_BYTES_USED` bigint(20) NOT NULL COMMENT 'Lowest number of bytes used.',
  `CURRENT_NUMBER_OF_BYTES_USED` bigint(20) NOT NULL COMMENT 'Current number of bytes used (total allocated minus total freed).',
  `HIGH_NUMBER_OF_BYTES_USED` bigint(20) NOT NULL COMMENT 'Highest number of bytes used.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `memory_summary_by_thread_by_event_name`
--

LOCK TABLES `memory_summary_by_thread_by_event_name` WRITE;
/*!40000 ALTER TABLE `memory_summary_by_thread_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `memory_summary_by_thread_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `memory_summary_by_user_by_event_name`
--

DROP TABLE IF EXISTS `memory_summary_by_user_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `memory_summary_by_user_by_event_name` (
  `USER` char(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'User portion of the account.',
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name.',
  `COUNT_ALLOC` bigint(20) unsigned NOT NULL COMMENT 'Total number of allocations to memory.',
  `COUNT_FREE` bigint(20) unsigned NOT NULL COMMENT 'Total number of attempts to free the allocated memory.',
  `SUM_NUMBER_OF_BYTES_ALLOC` bigint(20) unsigned NOT NULL COMMENT 'Total number of bytes allocated.',
  `SUM_NUMBER_OF_BYTES_FREE` bigint(20) unsigned NOT NULL COMMENT 'Total number of bytes freed',
  `LOW_COUNT_USED` bigint(20) NOT NULL COMMENT 'Lowest number of allocated blocks (lowest value of CURRENT_COUNT_USED).',
  `CURRENT_COUNT_USED` bigint(20) NOT NULL COMMENT 'Currently allocated blocks that have not been freed (COUNT_ALLOC minus COUNT_FREE).',
  `HIGH_COUNT_USED` bigint(20) NOT NULL COMMENT 'Highest number of allocated blocks (highest value of CURRENT_COUNT_USED).',
  `LOW_NUMBER_OF_BYTES_USED` bigint(20) NOT NULL COMMENT 'Lowest number of bytes used.',
  `CURRENT_NUMBER_OF_BYTES_USED` bigint(20) NOT NULL COMMENT 'Current number of bytes used (total allocated minus total freed).',
  `HIGH_NUMBER_OF_BYTES_USED` bigint(20) NOT NULL COMMENT 'Highest number of bytes used.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `memory_summary_by_user_by_event_name`
--

LOCK TABLES `memory_summary_by_user_by_event_name` WRITE;
/*!40000 ALTER TABLE `memory_summary_by_user_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `memory_summary_by_user_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `memory_summary_global_by_event_name`
--

DROP TABLE IF EXISTS `memory_summary_global_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `memory_summary_global_by_event_name` (
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Event name.',
  `COUNT_ALLOC` bigint(20) unsigned NOT NULL COMMENT 'Total number of allocations to memory.',
  `COUNT_FREE` bigint(20) unsigned NOT NULL COMMENT 'Total number of attempts to free the allocated memory.',
  `SUM_NUMBER_OF_BYTES_ALLOC` bigint(20) unsigned NOT NULL COMMENT 'Total number of bytes allocated.',
  `SUM_NUMBER_OF_BYTES_FREE` bigint(20) unsigned NOT NULL COMMENT 'Total number of bytes freed',
  `LOW_COUNT_USED` bigint(20) NOT NULL COMMENT 'Lowest number of allocated blocks (lowest value of CURRENT_COUNT_USED).',
  `CURRENT_COUNT_USED` bigint(20) NOT NULL COMMENT 'Currently allocated blocks that have not been freed (COUNT_ALLOC minus COUNT_FREE).',
  `HIGH_COUNT_USED` bigint(20) NOT NULL COMMENT 'Highest number of allocated blocks (highest value of CURRENT_COUNT_USED).',
  `LOW_NUMBER_OF_BYTES_USED` bigint(20) NOT NULL COMMENT 'Lowest number of bytes used.',
  `CURRENT_NUMBER_OF_BYTES_USED` bigint(20) NOT NULL COMMENT 'Current number of bytes used (total allocated minus total freed).',
  `HIGH_NUMBER_OF_BYTES_USED` bigint(20) NOT NULL COMMENT 'Highest number of bytes used.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `memory_summary_global_by_event_name`
--

LOCK TABLES `memory_summary_global_by_event_name` WRITE;
/*!40000 ALTER TABLE `memory_summary_global_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `memory_summary_global_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `metadata_locks`
--

DROP TABLE IF EXISTS `metadata_locks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `metadata_locks` (
  `OBJECT_TYPE` varchar(64) NOT NULL COMMENT 'Object type. One of BACKUP, COMMIT, EVENT, FUNCTION, GLOBAL, LOCKING SERVICE, PROCEDURE, SCHEMA, TABLE, TABLESPACE, TRIGGER (unused) or USER LEVEL LOCK.',
  `OBJECT_SCHEMA` varchar(64) DEFAULT NULL COMMENT 'Object schema.',
  `OBJECT_NAME` varchar(64) DEFAULT NULL COMMENT 'Object name.',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned NOT NULL COMMENT 'Address in memory of the instrumented object.',
  `LOCK_TYPE` varchar(32) NOT NULL COMMENT 'Lock type. One of BACKUP_FTWRL1, BACKUP_START, BACKUP_TRANS_DML, EXCLUSIVE, INTENTION_EXCLUSIVE, SHARED, SHARED_HIGH_PRIO, SHARED_NO_READ_WRITE, SHARED_NO_WRITE, SHARED_READ, SHARED_UPGRADABLE or SHARED_WRITE.',
  `LOCK_DURATION` varchar(32) NOT NULL COMMENT 'Lock duration. One of EXPLICIT (locks released by explicit action, for example a global lock acquired with FLUSH TABLES WITH READ LOCK) , STATEMENT (locks implicitly released at statement end) or TRANSACTION (locks implicitly released at transaction end).',
  `LOCK_STATUS` varchar(32) NOT NULL COMMENT 'Lock status. One of GRANTED, KILLED, PENDING, POST_RELEASE_NOTIFY, PRE_ACQUIRE_NOTIFY, TIMEOUT or VICTIM.',
  `SOURCE` varchar(64) DEFAULT NULL COMMENT 'Source file containing the instrumented code that produced the event, as well as the line number where the instrumentation occurred. This allows one to examine the source code involved.',
  `OWNER_THREAD_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'Thread that requested the lock.',
  `OWNER_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'Event that requested the lock.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `metadata_locks`
--

LOCK TABLES `metadata_locks` WRITE;
/*!40000 ALTER TABLE `metadata_locks` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `metadata_locks` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `mutex_instances`
--

DROP TABLE IF EXISTS `mutex_instances`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `mutex_instances` (
  `NAME` varchar(128) NOT NULL COMMENT 'Instrument name associated with the mutex.',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned NOT NULL COMMENT 'Memory address of the instrumented mutex.',
  `LOCKED_BY_THREAD_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'The THREAD_ID of the locking thread if a thread has a mutex locked, otherwise NULL.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `mutex_instances`
--

LOCK TABLES `mutex_instances` WRITE;
/*!40000 ALTER TABLE `mutex_instances` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `mutex_instances` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `objects_summary_global_by_type`
--

DROP TABLE IF EXISTS `objects_summary_global_by_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `objects_summary_global_by_type` (
  `OBJECT_TYPE` varchar(64) DEFAULT NULL COMMENT 'Groups records together with OBJECT_SCHEMA and OBJECT_NAME.',
  `OBJECT_SCHEMA` varchar(64) DEFAULT NULL COMMENT 'Groups records together with OBJECT_TYPE and OBJECT_NAME.',
  `OBJECT_NAME` varchar(64) DEFAULT NULL COMMENT 'Groups records together with OBJECT_SCHEMA and OBJECT_TYPE.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `objects_summary_global_by_type`
--

LOCK TABLES `objects_summary_global_by_type` WRITE;
/*!40000 ALTER TABLE `objects_summary_global_by_type` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `objects_summary_global_by_type` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `performance_timers`
--

DROP TABLE IF EXISTS `performance_timers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `performance_timers` (
  `TIMER_NAME` enum('CYCLE','NANOSECOND','MICROSECOND','MILLISECOND','TICK') NOT NULL COMMENT 'Time name, used in the setup_timers table.',
  `TIMER_FREQUENCY` bigint(20) DEFAULT NULL COMMENT 'Number of timer units per second. Dependent on the processor speed.',
  `TIMER_RESOLUTION` bigint(20) DEFAULT NULL COMMENT 'Number of timer units by which timed values increase each time.',
  `TIMER_OVERHEAD` bigint(20) DEFAULT NULL COMMENT 'Minimum timer overhead, determined during initialization by calling the timer 20 times and selecting the smallest value. Total overhead will be at least double this, as the timer is called at the beginning and end of each timed event.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `performance_timers`
--

LOCK TABLES `performance_timers` WRITE;
/*!40000 ALTER TABLE `performance_timers` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `performance_timers` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `prepared_statements_instances`
--

DROP TABLE IF EXISTS `prepared_statements_instances`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `prepared_statements_instances` (
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned NOT NULL COMMENT 'The address in memory of the instrumented prepared statement.',
  `STATEMENT_ID` bigint(20) unsigned NOT NULL COMMENT 'The internal statement ID assigned by the server.',
  `STATEMENT_NAME` varchar(64) DEFAULT NULL COMMENT 'For the binary protocol, this column is NULL. For the text protocol, this column is the external statement name assigned by the user.',
  `SQL_TEXT` longtext NOT NULL COMMENT 'The prepared statement text, with ? placeholder markers.',
  `OWNER_THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'Event thread id that created the prepared statement.',
  `OWNER_EVENT_ID` bigint(20) unsigned NOT NULL COMMENT 'Event id that created the prepared statement.',
  `OWNER_OBJECT_TYPE` enum('EVENT','FUNCTION','PROCEDURE','TABLE','TRIGGER') DEFAULT NULL COMMENT 'NULL for a prepared statement created by a client session. Type of the stored program that created the prepared statement.',
  `OWNER_OBJECT_SCHEMA` varchar(64) DEFAULT NULL COMMENT 'NULL for a prepared statement created by a client session. Schema of the stored program that created the prepared statement.',
  `OWNER_OBJECT_NAME` varchar(64) DEFAULT NULL COMMENT 'NULL for a prepared statement created by a client session. Name of the stored program that created the prepared statement.',
  `TIMER_PREPARE` bigint(20) unsigned NOT NULL COMMENT 'The time spent executing the statement preparation itself.',
  `COUNT_REPREPARE` bigint(20) unsigned NOT NULL COMMENT 'The number of times the statement was reprepared internally.',
  `COUNT_EXECUTE` bigint(20) unsigned NOT NULL COMMENT 'Total times the prepared statement was executed.',
  `SUM_TIMER_EXECUTE` bigint(20) unsigned NOT NULL COMMENT 'Total time spent executing all prepared statements.',
  `MIN_TIMER_EXECUTE` bigint(20) unsigned NOT NULL COMMENT 'Minimum time spent executing any of the prepared statements.',
  `AVG_TIMER_EXECUTE` bigint(20) unsigned NOT NULL COMMENT 'Average time spent executing any of the prepared statements.',
  `MAX_TIMER_EXECUTE` bigint(20) unsigned NOT NULL COMMENT 'Maximum time spent executing any of the prepared statements.',
  `SUM_LOCK_TIME` bigint(20) unsigned NOT NULL COMMENT 'The total time spent (in picoseconds) waiting for table locks for the prepared statements.',
  `SUM_ERRORS` bigint(20) unsigned NOT NULL COMMENT 'The total number of errors that occurend for the prepared statements.',
  `SUM_WARNINGS` bigint(20) unsigned NOT NULL COMMENT 'The total number of warnings that occurend for the prepared statements.',
  `SUM_ROWS_AFFECTED` bigint(20) unsigned NOT NULL COMMENT 'The total number of affected rows by the prepared statements.',
  `SUM_ROWS_SENT` bigint(20) unsigned NOT NULL COMMENT 'The total number of rows returned by the prepared statements.',
  `SUM_ROWS_EXAMINED` bigint(20) unsigned NOT NULL COMMENT 'The total number of rows examined by the prepared statements.',
  `SUM_CREATED_TMP_DISK_TABLES` bigint(20) unsigned NOT NULL COMMENT 'The total number of on-disk temporary tables created by the prepared statements.',
  `SUM_CREATED_TMP_TABLES` bigint(20) unsigned NOT NULL COMMENT 'The total number of in-memory temporary tables created by the prepared statements.',
  `SUM_SELECT_FULL_JOIN` bigint(20) unsigned NOT NULL COMMENT 'The total number of full joins executed by the prepared statements.',
  `SUM_SELECT_FULL_RANGE_JOIN` bigint(20) unsigned NOT NULL COMMENT 'The total number of range search joins executed by the prepared statements.',
  `SUM_SELECT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'The total number of joins that used ranges on the first table executed by the prepared statements.',
  `SUM_SELECT_RANGE_CHECK` bigint(20) unsigned NOT NULL COMMENT 'The total number of joins that check for key usage after each row executed by the prepared statements.',
  `SUM_SELECT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'The total number of joins that did a full scan of the first table executed by the prepared statements.',
  `SUM_SORT_MERGE_PASSES` bigint(20) unsigned NOT NULL COMMENT 'The total number of merge passes that the sort algorithm has had to do for the prepared statements.',
  `SUM_SORT_RANGE` bigint(20) unsigned NOT NULL COMMENT 'The total number of sorts that were done using ranges for the prepared statements.',
  `SUM_SORT_ROWS` bigint(20) unsigned NOT NULL COMMENT 'The total number of sorted rows that were sorted by the prepared statements.',
  `SUM_SORT_SCAN` bigint(20) unsigned NOT NULL COMMENT 'The total number of sorts that were done by scanning the table by the prepared statements.',
  `SUM_NO_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'The total number of statements that performed a table scan without using an index.',
  `SUM_NO_GOOD_INDEX_USED` bigint(20) unsigned NOT NULL COMMENT 'The total number of statements where no good index was found.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `prepared_statements_instances`
--

LOCK TABLES `prepared_statements_instances` WRITE;
/*!40000 ALTER TABLE `prepared_statements_instances` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `prepared_statements_instances` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `replication_applier_configuration`
--

DROP TABLE IF EXISTS `replication_applier_configuration`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `replication_applier_configuration` (
  `CHANNEL_NAME` varchar(256) NOT NULL COMMENT 'Replication channel name.',
  `DESIRED_DELAY` int(11) NOT NULL COMMENT 'Target number of seconds the replica should be delayed to the master.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `replication_applier_configuration`
--

LOCK TABLES `replication_applier_configuration` WRITE;
/*!40000 ALTER TABLE `replication_applier_configuration` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `replication_applier_configuration` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `replication_applier_status`
--

DROP TABLE IF EXISTS `replication_applier_status`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `replication_applier_status` (
  `CHANNEL_NAME` varchar(256) NOT NULL COMMENT 'The replication channel name.',
  `SERVICE_STATE` enum('ON','OFF') NOT NULL COMMENT 'Shows ON when the replication channel''s applier threads are active or idle, OFF means that the applier threads are not active.',
  `REMAINING_DELAY` int(10) unsigned DEFAULT NULL COMMENT 'Seconds the replica needs to wait to reach the desired delay from master.',
  `COUNT_TRANSACTIONS_RETRIES` bigint(20) unsigned NOT NULL COMMENT 'The number of retries that were made because the replication SQL thread failed to apply a transaction.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `replication_applier_status`
--

LOCK TABLES `replication_applier_status` WRITE;
/*!40000 ALTER TABLE `replication_applier_status` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `replication_applier_status` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `replication_applier_status_by_coordinator`
--

DROP TABLE IF EXISTS `replication_applier_status_by_coordinator`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `replication_applier_status_by_coordinator` (
  `CHANNEL_NAME` varchar(256) NOT NULL COMMENT 'Replication channel name.',
  `THREAD_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'The SQL/coordinator thread ID.',
  `SERVICE_STATE` enum('ON','OFF') NOT NULL COMMENT 'ON (thread exists and is active or idle) or OFF (thread no longer exists).',
  `LAST_ERROR_NUMBER` int(11) NOT NULL COMMENT 'Last error number that caused the SQL/coordinator thread to stop.',
  `LAST_ERROR_MESSAGE` varchar(1024) NOT NULL COMMENT 'Last error message that caused the SQL/coordinator thread to stop.',
  `LAST_ERROR_TIMESTAMP` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp() COMMENT 'Timestamp that shows when the most recent SQL/coordinator error occurred.',
  `LAST_SEEN_TRANSACTION` char(57) NOT NULL COMMENT 'The transaction the worker has last seen.',
  `LAST_TRANS_RETRY_COUNT` int(11) NOT NULL COMMENT 'Total number of retries attempted by last transaction.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `replication_applier_status_by_coordinator`
--

LOCK TABLES `replication_applier_status_by_coordinator` WRITE;
/*!40000 ALTER TABLE `replication_applier_status_by_coordinator` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `replication_applier_status_by_coordinator` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `replication_applier_status_by_worker`
--

DROP TABLE IF EXISTS `replication_applier_status_by_worker`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `replication_applier_status_by_worker` (
  `CHANNEL_NAME` varchar(256) NOT NULL COMMENT 'Name of replication channel through which the transaction is received.',
  `THREAD_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'Thread_Id as displayed in the performance_schema.threads table for thread with name ''thread/sql/rpl_parallel''. THREAD_ID will be NULL when worker threads are stopped due to error/force stop.',
  `SERVICE_STATE` enum('ON','OFF') NOT NULL COMMENT 'Whether or not the thread is running.',
  `LAST_SEEN_TRANSACTION` char(57) NOT NULL COMMENT 'Last GTID executed by worker',
  `LAST_ERROR_NUMBER` int(11) NOT NULL COMMENT 'Last Error that occurred on a particular worker.',
  `LAST_ERROR_MESSAGE` varchar(1024) NOT NULL COMMENT 'Last error specific message.',
  `LAST_ERROR_TIMESTAMP` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp() COMMENT 'Time stamp of last error.',
  `WORKER_IDLE_TIME` bigint(20) unsigned NOT NULL COMMENT 'Total idle time in seconds that the worker thread has spent waiting for work from SQL thread.',
  `LAST_TRANS_RETRY_COUNT` int(11) NOT NULL COMMENT 'Total number of retries attempted by last transaction.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `replication_applier_status_by_worker`
--

LOCK TABLES `replication_applier_status_by_worker` WRITE;
/*!40000 ALTER TABLE `replication_applier_status_by_worker` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `replication_applier_status_by_worker` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `replication_connection_configuration`
--

DROP TABLE IF EXISTS `replication_connection_configuration`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `replication_connection_configuration` (
  `CHANNEL_NAME` varchar(256) NOT NULL COMMENT 'The replication channel used.',
  `HOST` char(60) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin NOT NULL COMMENT 'The host name of the source that the replica is connected to.',
  `PORT` int(11) NOT NULL COMMENT 'The port used to connect to the source.',
  `USER` char(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin NOT NULL COMMENT 'The user name of the replication user account used to connect to the source.',
  `USING_GTID` enum('NO','CURRENT_POS','SLAVE_POS') NOT NULL COMMENT 'Whether replication is using GTIDs or not',
  `SSL_ALLOWED` enum('YES','NO','IGNORED') NOT NULL COMMENT 'Whether SSL is allowed for the replica connection.',
  `SSL_CA_FILE` varchar(512) NOT NULL COMMENT 'Path to the file that contains one or more certificates for trusted Certificate Authorities (CA) to use for TLS.',
  `SSL_CA_PATH` varchar(512) NOT NULL COMMENT 'Path to a directory that contains one or more PEM files that contain X509 certificates for a trusted Certificate Authority (CA) to use for TLS.',
  `SSL_CERTIFICATE` varchar(512) NOT NULL COMMENT 'Path to the certificate used to authenticate the master.',
  `SSL_CIPHER` varchar(512) NOT NULL COMMENT 'Which cipher is used for encription.',
  `SSL_KEY` varchar(512) NOT NULL COMMENT 'Path to the private key used for TLS.',
  `SSL_VERIFY_SERVER_CERTIFICATE` enum('YES','NO') NOT NULL COMMENT 'Whether the server certificate is verified as part of the SSL connection',
  `SSL_CRL_FILE` varchar(255) NOT NULL COMMENT 'Path to the PEM file containing one or more revoked X.509 certificates.',
  `SSL_CRL_PATH` varchar(255) NOT NULL COMMENT 'PATH to a folder containing PEM files containing one or more revoked X.509 certificates.',
  `CONNECTION_RETRY_INTERVAL` int(11) NOT NULL COMMENT 'The number of seconds between connect retries.',
  `CONNECTION_RETRY_COUNT` bigint(20) unsigned NOT NULL COMMENT 'The number of times the replica can attempt to reconnect to the source in the event of a lost connection.',
  `HEARTBEAT_INTERVAL` double(10,3) unsigned NOT NULL COMMENT 'Number of seconds after which a heartbeat will be sent.',
  `IGNORE_SERVER_IDS` longtext NOT NULL COMMENT 'Binary log events from servers (ids) to ignore.',
  `REPL_DO_DOMAIN_IDS` longtext NOT NULL COMMENT 'Only apply binary logs from these domain ids.',
  `REPL_IGNORE_DOMAIN_IDS` longtext NOT NULL COMMENT 'Binary log events from domains to ignore.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `replication_connection_configuration`
--

LOCK TABLES `replication_connection_configuration` WRITE;
/*!40000 ALTER TABLE `replication_connection_configuration` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `replication_connection_configuration` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `rwlock_instances`
--

DROP TABLE IF EXISTS `rwlock_instances`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `rwlock_instances` (
  `NAME` varchar(128) NOT NULL COMMENT 'Instrument name associated with the read write lock',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned NOT NULL COMMENT 'Address in memory of the instrumented lock',
  `WRITE_LOCKED_BY_THREAD_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'THREAD_ID of the locking thread if locked in write (exclusive) mode, otherwise NULL.',
  `READ_LOCKED_BY_COUNT` int(10) unsigned NOT NULL COMMENT 'Count of current read locks held'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `rwlock_instances`
--

LOCK TABLES `rwlock_instances` WRITE;
/*!40000 ALTER TABLE `rwlock_instances` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `rwlock_instances` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `session_account_connect_attrs`
--

DROP TABLE IF EXISTS `session_account_connect_attrs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `session_account_connect_attrs` (
  `PROCESSLIST_ID` int(11) NOT NULL COMMENT 'Session connection identifier.',
  `ATTR_NAME` varchar(32) NOT NULL COMMENT 'Attribute name.',
  `ATTR_VALUE` varchar(1024) DEFAULT NULL COMMENT 'Attribute value.',
  `ORDINAL_POSITION` int(11) DEFAULT NULL COMMENT 'Order in which attribute was added to the connection attributes.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `session_account_connect_attrs`
--

LOCK TABLES `session_account_connect_attrs` WRITE;
/*!40000 ALTER TABLE `session_account_connect_attrs` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `session_account_connect_attrs` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `session_connect_attrs`
--

DROP TABLE IF EXISTS `session_connect_attrs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `session_connect_attrs` (
  `PROCESSLIST_ID` int(11) NOT NULL COMMENT 'Session connection identifier.',
  `ATTR_NAME` varchar(32) NOT NULL COMMENT 'Attribute name.',
  `ATTR_VALUE` varchar(1024) DEFAULT NULL COMMENT 'Attribute value.',
  `ORDINAL_POSITION` int(11) DEFAULT NULL COMMENT 'Order in which attribute was added to the connection attributes.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `session_connect_attrs`
--

LOCK TABLES `session_connect_attrs` WRITE;
/*!40000 ALTER TABLE `session_connect_attrs` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `session_connect_attrs` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `session_status`
--

DROP TABLE IF EXISTS `session_status`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `session_status` (
  `VARIABLE_NAME` varchar(64) NOT NULL COMMENT 'The session status variable name.',
  `VARIABLE_VALUE` varchar(1024) DEFAULT NULL COMMENT 'The session status variable value.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `session_status`
--

LOCK TABLES `session_status` WRITE;
/*!40000 ALTER TABLE `session_status` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `session_status` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `setup_actors`
--

DROP TABLE IF EXISTS `setup_actors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `setup_actors` (
  `HOST` char(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin NOT NULL DEFAULT '%' COMMENT 'Host name, either a literal, or the % wildcard representing any host.',
  `USER` char(128) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin NOT NULL DEFAULT '%' COMMENT 'User name, either a literal or the % wildcard representing any name.',
  `ROLE` char(128) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin NOT NULL DEFAULT '%' COMMENT 'Unused',
  `ENABLED` enum('YES','NO') NOT NULL DEFAULT 'YES' COMMENT 'Whether to enable instrumentation for foreground threads matched by the row.',
  `HISTORY` enum('YES','NO') NOT NULL DEFAULT 'YES' COMMENT 'Whether to log historical events for foreground threads matched by the row.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `setup_actors`
--

LOCK TABLES `setup_actors` WRITE;
/*!40000 ALTER TABLE `setup_actors` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `setup_actors` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `setup_consumers`
--

DROP TABLE IF EXISTS `setup_consumers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `setup_consumers` (
  `NAME` varchar(64) NOT NULL COMMENT 'Consumer name',
  `ENABLED` enum('YES','NO') NOT NULL COMMENT 'YES or NO for whether or not the consumer is enabled. You can modify this column to ensure that event information is added, or is not added.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `setup_consumers`
--

LOCK TABLES `setup_consumers` WRITE;
/*!40000 ALTER TABLE `setup_consumers` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `setup_consumers` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `setup_instruments`
--

DROP TABLE IF EXISTS `setup_instruments`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `setup_instruments` (
  `NAME` varchar(128) NOT NULL COMMENT 'Instrument name',
  `ENABLED` enum('YES','NO') NOT NULL COMMENT 'Whether or not the instrument is enabled. It can be disabled, and the instrument will produce no events.',
  `TIMED` enum('YES','NO') NOT NULL COMMENT 'Whether or not the instrument is timed. It can be set, but if disabled, events produced by the instrument will have NULL values for the corresponding TIMER_START, TIMER_END, and TIMER_WAIT values.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `setup_instruments`
--

LOCK TABLES `setup_instruments` WRITE;
/*!40000 ALTER TABLE `setup_instruments` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `setup_instruments` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `setup_objects`
--

DROP TABLE IF EXISTS `setup_objects`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `setup_objects` (
  `OBJECT_TYPE` enum('EVENT','FUNCTION','PROCEDURE','TABLE','TRIGGER') NOT NULL DEFAULT 'TABLE' COMMENT 'Type of object to instrument.',
  `OBJECT_SCHEMA` varchar(64) DEFAULT '%' COMMENT 'Schema containing the object, either the literal or % for any schema.',
  `OBJECT_NAME` varchar(64) NOT NULL DEFAULT '%' COMMENT 'Name of the instrumented object, either the literal or % for any object.',
  `ENABLED` enum('YES','NO') NOT NULL DEFAULT 'YES' COMMENT 'Whether the object''s events are instrumented or not. Can be disabled, in which case monitoring is not enabled for those objects.',
  `TIMED` enum('YES','NO') NOT NULL DEFAULT 'YES' COMMENT 'Whether the object''s events are timed or not. Can be modified.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `setup_objects`
--

LOCK TABLES `setup_objects` WRITE;
/*!40000 ALTER TABLE `setup_objects` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `setup_objects` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `setup_timers`
--

DROP TABLE IF EXISTS `setup_timers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `setup_timers` (
  `NAME` varchar(64) NOT NULL COMMENT 'Type of instrument the timer is used for.',
  `TIMER_NAME` enum('CYCLE','NANOSECOND','MICROSECOND','MILLISECOND','TICK') NOT NULL COMMENT 'Timer applying to the instrument type. Can be modified.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `setup_timers`
--

LOCK TABLES `setup_timers` WRITE;
/*!40000 ALTER TABLE `setup_timers` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `setup_timers` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `socket_instances`
--

DROP TABLE IF EXISTS `socket_instances`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `socket_instances` (
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'NAME from the setup_instruments table, and the name of the wait/io/socket/* instrument that produced the event.',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned NOT NULL COMMENT 'Memory address of the object.',
  `THREAD_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'Thread identifier that the server assigns to each socket.',
  `SOCKET_ID` int(11) NOT NULL COMMENT 'The socket''s internal file handle.',
  `IP` varchar(64) NOT NULL COMMENT 'Client IP address. Blank for Unix socket file, otherwise an IPv4 or IPv6 address. Together with the PORT identifies the connection.',
  `PORT` int(11) NOT NULL COMMENT 'TCP/IP port number, from 0 to 65535. Together with the IP identifies the connection.',
  `STATE` enum('IDLE','ACTIVE') NOT NULL COMMENT 'Socket status, either IDLE if waiting to receive a request from a client, or ACTIVE'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `socket_instances`
--

LOCK TABLES `socket_instances` WRITE;
/*!40000 ALTER TABLE `socket_instances` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `socket_instances` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `socket_summary_by_event_name`
--

DROP TABLE IF EXISTS `socket_summary_by_event_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `socket_summary_by_event_name` (
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Socket instrument.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.',
  `COUNT_READ` bigint(20) unsigned NOT NULL COMMENT 'Number of all read operations, including RECV, RECVFROM, and RECVMSG.',
  `SUM_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all read operations that are timed.',
  `MIN_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all read operations that are timed.',
  `AVG_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all read operations that are timed.',
  `MAX_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all read operations that are timed.',
  `SUM_NUMBER_OF_BYTES_READ` bigint(20) unsigned NOT NULL COMMENT 'Bytes read by read operations.',
  `COUNT_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Number of all write operations, including SEND, SENDTO, and SENDMSG.',
  `SUM_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all write operations that are timed.',
  `MIN_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all write operations that are timed.',
  `AVG_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all write operations that are timed.',
  `MAX_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all write operations that are timed.',
  `SUM_NUMBER_OF_BYTES_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Bytes written by write operations.',
  `COUNT_MISC` bigint(20) unsigned NOT NULL COMMENT 'Number of all miscellaneous operations not counted above, including CONNECT, LISTEN, ACCEPT, CLOSE, and SHUTDOWN.',
  `SUM_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all miscellaneous operations that are timed.',
  `MIN_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all miscellaneous operations that are timed.',
  `AVG_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all miscellaneous operations that are timed.',
  `MAX_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all miscellaneous operations that are timed.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `socket_summary_by_event_name`
--

LOCK TABLES `socket_summary_by_event_name` WRITE;
/*!40000 ALTER TABLE `socket_summary_by_event_name` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `socket_summary_by_event_name` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `socket_summary_by_instance`
--

DROP TABLE IF EXISTS `socket_summary_by_instance`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `socket_summary_by_instance` (
  `EVENT_NAME` varchar(128) NOT NULL COMMENT 'Socket instrument.',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned NOT NULL COMMENT 'Address in memory.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.',
  `COUNT_READ` bigint(20) unsigned NOT NULL COMMENT 'Number of all read operations, including RECV, RECVFROM, and RECVMSG.',
  `SUM_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all read operations that are timed.',
  `MIN_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all read operations that are timed.',
  `AVG_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all read operations that are timed.',
  `MAX_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all read operations that are timed.',
  `SUM_NUMBER_OF_BYTES_READ` bigint(20) unsigned NOT NULL COMMENT 'Bytes read by read operations.',
  `COUNT_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Number of all write operations, including SEND, SENDTO, and SENDMSG.',
  `SUM_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all write operations that are timed.',
  `MIN_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all write operations that are timed.',
  `AVG_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all write operations that are timed.',
  `MAX_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all write operations that are timed.',
  `SUM_NUMBER_OF_BYTES_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Bytes written by write operations.',
  `COUNT_MISC` bigint(20) unsigned NOT NULL COMMENT 'Number of all miscellaneous operations not counted above, including CONNECT, LISTEN, ACCEPT, CLOSE, and SHUTDOWN.',
  `SUM_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all miscellaneous operations that are timed.',
  `MIN_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all miscellaneous operations that are timed.',
  `AVG_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all miscellaneous operations that are timed.',
  `MAX_TIMER_MISC` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all miscellaneous operations that are timed.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `socket_summary_by_instance`
--

LOCK TABLES `socket_summary_by_instance` WRITE;
/*!40000 ALTER TABLE `socket_summary_by_instance` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `socket_summary_by_instance` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `status_by_account`
--

DROP TABLE IF EXISTS `status_by_account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `status_by_account` (
  `USER` char(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'User for which the status variable is reported.',
  `HOST` char(60) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'Host for which the status variable is reported.',
  `VARIABLE_NAME` varchar(64) NOT NULL COMMENT 'Status variable name.',
  `VARIABLE_VALUE` varchar(1024) DEFAULT NULL COMMENT 'Aggregated status variable value.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `status_by_account`
--

LOCK TABLES `status_by_account` WRITE;
/*!40000 ALTER TABLE `status_by_account` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `status_by_account` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `status_by_host`
--

DROP TABLE IF EXISTS `status_by_host`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `status_by_host` (
  `HOST` char(60) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'Host for which the status variable is reported.',
  `VARIABLE_NAME` varchar(64) NOT NULL COMMENT 'Status variable name.',
  `VARIABLE_VALUE` varchar(1024) DEFAULT NULL COMMENT 'Aggregated status variable value.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `status_by_host`
--

LOCK TABLES `status_by_host` WRITE;
/*!40000 ALTER TABLE `status_by_host` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `status_by_host` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `status_by_thread`
--

DROP TABLE IF EXISTS `status_by_thread`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `status_by_thread` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'The thread identifier of the session in which the status variable is defined.',
  `VARIABLE_NAME` varchar(64) NOT NULL COMMENT 'Status variable name.',
  `VARIABLE_VALUE` varchar(1024) DEFAULT NULL COMMENT 'Aggregated status variable value.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `status_by_thread`
--

LOCK TABLES `status_by_thread` WRITE;
/*!40000 ALTER TABLE `status_by_thread` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `status_by_thread` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `status_by_user`
--

DROP TABLE IF EXISTS `status_by_user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `status_by_user` (
  `USER` char(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'User for which the status variable is reported.',
  `VARIABLE_NAME` varchar(64) NOT NULL COMMENT 'Status variable name.',
  `VARIABLE_VALUE` varchar(1024) DEFAULT NULL COMMENT 'Aggregated status variable value.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `status_by_user`
--

LOCK TABLES `status_by_user` WRITE;
/*!40000 ALTER TABLE `status_by_user` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `status_by_user` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `table_handles`
--

DROP TABLE IF EXISTS `table_handles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `table_handles` (
  `OBJECT_TYPE` varchar(64) NOT NULL COMMENT 'The table opened by a table handle.',
  `OBJECT_SCHEMA` varchar(64) NOT NULL COMMENT 'The schema that contains the object.',
  `OBJECT_NAME` varchar(64) NOT NULL COMMENT 'The name of the instrumented object.',
  `OBJECT_INSTANCE_BEGIN` bigint(20) unsigned NOT NULL COMMENT 'The table handle address in memory.',
  `OWNER_THREAD_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'The thread owning the table handle.',
  `OWNER_EVENT_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'The event which caused the table handle to be opened.',
  `INTERNAL_LOCK` varchar(64) DEFAULT NULL COMMENT 'The table lock used at the SQL level.',
  `EXTERNAL_LOCK` varchar(64) DEFAULT NULL COMMENT 'The table lock used at the storage engine level.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `table_handles`
--

LOCK TABLES `table_handles` WRITE;
/*!40000 ALTER TABLE `table_handles` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `table_handles` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `table_io_waits_summary_by_index_usage`
--

DROP TABLE IF EXISTS `table_io_waits_summary_by_index_usage`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `table_io_waits_summary_by_index_usage` (
  `OBJECT_TYPE` varchar(64) DEFAULT NULL COMMENT 'TABLE in the case of all indexes.',
  `OBJECT_SCHEMA` varchar(64) DEFAULT NULL COMMENT 'Schema name.',
  `OBJECT_NAME` varchar(64) DEFAULT NULL COMMENT 'Table name.',
  `INDEX_NAME` varchar(64) DEFAULT NULL COMMENT 'Index name, or PRIMARY for the primary index, NULL for no index (inserts are counted in this case).',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events and the sum of the x_READ and x_WRITE columns.',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.',
  `COUNT_READ` bigint(20) unsigned NOT NULL COMMENT 'Number of all read operations, and the sum of the equivalent x_FETCH columns.',
  `SUM_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all read operations that are timed.',
  `MIN_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all read operations that are timed.',
  `AVG_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all read operations that are timed.',
  `MAX_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all read operations that are timed.',
  `COUNT_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Number of all write operations, and the sum of the equivalent x_INSERT, x_UPDATE and x_DELETE columns.',
  `SUM_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all write operations that are timed.',
  `MIN_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all write operations that are timed.',
  `AVG_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all write operations that are timed.',
  `MAX_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all write operations that are timed.',
  `COUNT_FETCH` bigint(20) unsigned NOT NULL COMMENT 'Number of all fetch operations.',
  `SUM_TIMER_FETCH` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all fetch operations that are timed.',
  `MIN_TIMER_FETCH` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all fetch operations that are timed.',
  `AVG_TIMER_FETCH` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all fetch operations that are timed.',
  `MAX_TIMER_FETCH` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all fetch operations that are timed.',
  `COUNT_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Number of all insert operations.',
  `SUM_TIMER_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all insert operations that are timed.',
  `MIN_TIMER_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all insert operations that are timed.',
  `AVG_TIMER_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all insert operations that are timed.',
  `MAX_TIMER_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all insert operations that are timed.',
  `COUNT_UPDATE` bigint(20) unsigned NOT NULL COMMENT 'Number of all update operations.',
  `SUM_TIMER_UPDATE` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all update operations that are timed.',
  `MIN_TIMER_UPDATE` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all update operations that are timed.',
  `AVG_TIMER_UPDATE` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all update operations that are timed.',
  `MAX_TIMER_UPDATE` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all update operations that are timed.',
  `COUNT_DELETE` bigint(20) unsigned NOT NULL COMMENT 'Number of all delete operations.',
  `SUM_TIMER_DELETE` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all delete operations that are timed.',
  `MIN_TIMER_DELETE` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all delete operations that are timed.',
  `AVG_TIMER_DELETE` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all delete operations that are timed.',
  `MAX_TIMER_DELETE` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all delete operations that are timed.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `table_io_waits_summary_by_index_usage`
--

LOCK TABLES `table_io_waits_summary_by_index_usage` WRITE;
/*!40000 ALTER TABLE `table_io_waits_summary_by_index_usage` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `table_io_waits_summary_by_index_usage` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `table_io_waits_summary_by_table`
--

DROP TABLE IF EXISTS `table_io_waits_summary_by_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `table_io_waits_summary_by_table` (
  `OBJECT_TYPE` varchar(64) DEFAULT NULL COMMENT 'Since this table records waits by table, always set to TABLE.',
  `OBJECT_SCHEMA` varchar(64) DEFAULT NULL COMMENT 'Schema name.',
  `OBJECT_NAME` varchar(64) DEFAULT NULL COMMENT 'Table name.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events and the sum of the x_READ and x_WRITE columns.',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.',
  `COUNT_READ` bigint(20) unsigned NOT NULL COMMENT 'Number of all read operations, and the sum of the equivalent x_FETCH columns.',
  `SUM_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all read operations that are timed.',
  `MIN_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all read operations that are timed.',
  `AVG_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all read operations that are timed.',
  `MAX_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all read operations that are timed.',
  `COUNT_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Number of all write operations, and the sum of the equivalent x_INSERT, x_UPDATE and x_DELETE columns.',
  `SUM_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all write operations that are timed.',
  `MIN_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all write operations that are timed.',
  `AVG_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all write operations that are timed.',
  `MAX_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all write operations that are timed.',
  `COUNT_FETCH` bigint(20) unsigned NOT NULL COMMENT 'Number of all fetch operations.',
  `SUM_TIMER_FETCH` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all fetch operations that are timed.',
  `MIN_TIMER_FETCH` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all fetch operations that are timed.',
  `AVG_TIMER_FETCH` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all fetch operations that are timed.',
  `MAX_TIMER_FETCH` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all fetch operations that are timed.',
  `COUNT_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Number of all insert operations.',
  `SUM_TIMER_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all insert operations that are timed.',
  `MIN_TIMER_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all insert operations that are timed.',
  `AVG_TIMER_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all insert operations that are timed.',
  `MAX_TIMER_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all insert operations that are timed.',
  `COUNT_UPDATE` bigint(20) unsigned NOT NULL COMMENT 'Number of all update operations.',
  `SUM_TIMER_UPDATE` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all update operations that are timed.',
  `MIN_TIMER_UPDATE` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all update operations that are timed.',
  `AVG_TIMER_UPDATE` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all update operations that are timed.',
  `MAX_TIMER_UPDATE` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all update operations that are timed.',
  `COUNT_DELETE` bigint(20) unsigned NOT NULL COMMENT 'Number of all delete operations.',
  `SUM_TIMER_DELETE` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all delete operations that are timed.',
  `MIN_TIMER_DELETE` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all delete operations that are timed.',
  `AVG_TIMER_DELETE` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all delete operations that are timed.',
  `MAX_TIMER_DELETE` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all delete operations that are timed.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `table_io_waits_summary_by_table`
--

LOCK TABLES `table_io_waits_summary_by_table` WRITE;
/*!40000 ALTER TABLE `table_io_waits_summary_by_table` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `table_io_waits_summary_by_table` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `table_lock_waits_summary_by_table`
--

DROP TABLE IF EXISTS `table_lock_waits_summary_by_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `table_lock_waits_summary_by_table` (
  `OBJECT_TYPE` varchar(64) DEFAULT NULL COMMENT 'Since this table records waits by table, always set to TABLE.',
  `OBJECT_SCHEMA` varchar(64) DEFAULT NULL COMMENT 'Schema name.',
  `OBJECT_NAME` varchar(64) DEFAULT NULL COMMENT 'Table name.',
  `COUNT_STAR` bigint(20) unsigned NOT NULL COMMENT 'Number of summarized events and the sum of the x_READ and x_WRITE columns.',
  `SUM_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of the summarized events that are timed.',
  `MIN_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of the summarized events that are timed.',
  `AVG_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of the summarized events that are timed.',
  `MAX_TIMER_WAIT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of the summarized events that are timed.',
  `COUNT_READ` bigint(20) unsigned NOT NULL COMMENT 'Number of all read operations, and the sum of the equivalent x_READ_NORMAL, x_READ_WITH_SHARED_LOCKS, x_READ_HIGH_PRIORITY and x_READ_NO_INSERT columns.',
  `SUM_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all read operations that are timed.',
  `MIN_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all read operations that are timed.',
  `AVG_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all read operations that are timed.',
  `MAX_TIMER_READ` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all read operations that are timed.',
  `COUNT_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Number of all write operations, and the sum of the equivalent x_WRITE_ALLOW_WRITE, x_WRITE_CONCURRENT_INSERT, x_WRITE_DELAYED, x_WRITE_LOW_PRIORITY and x_WRITE_NORMAL columns.',
  `SUM_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all write operations that are timed.',
  `MIN_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all write operations that are timed.',
  `AVG_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all write operations that are timed.',
  `MAX_TIMER_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all write operations that are timed.',
  `COUNT_READ_NORMAL` bigint(20) unsigned NOT NULL COMMENT 'Number of all internal read normal locks.',
  `SUM_TIMER_READ_NORMAL` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all internal read normal locks that are timed.',
  `MIN_TIMER_READ_NORMAL` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all internal read normal locks that are timed.',
  `AVG_TIMER_READ_NORMAL` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all internal read normal locks that are timed.',
  `MAX_TIMER_READ_NORMAL` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all internal read normal locks that are timed.',
  `COUNT_READ_WITH_SHARED_LOCKS` bigint(20) unsigned NOT NULL COMMENT 'Number of all internal read with shared locks.',
  `SUM_TIMER_READ_WITH_SHARED_LOCKS` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all internal read with shared locks that are timed.',
  `MIN_TIMER_READ_WITH_SHARED_LOCKS` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all internal read with shared locks that are timed.',
  `AVG_TIMER_READ_WITH_SHARED_LOCKS` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all internal read with shared locks that are timed.',
  `MAX_TIMER_READ_WITH_SHARED_LOCKS` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all internal read with shared locks that are timed.',
  `COUNT_READ_HIGH_PRIORITY` bigint(20) unsigned NOT NULL COMMENT 'Number of all internal read high priority locks.',
  `SUM_TIMER_READ_HIGH_PRIORITY` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all internal read high priority locks that are timed.',
  `MIN_TIMER_READ_HIGH_PRIORITY` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all internal read high priority locks that are timed.',
  `AVG_TIMER_READ_HIGH_PRIORITY` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all internal read high priority locks that are timed.',
  `MAX_TIMER_READ_HIGH_PRIORITY` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all internal read high priority locks that are timed.',
  `COUNT_READ_NO_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Number of all internal read no insert locks.',
  `SUM_TIMER_READ_NO_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all internal read no insert locks that are timed.',
  `MIN_TIMER_READ_NO_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all internal read no insert locks that are timed.',
  `AVG_TIMER_READ_NO_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all internal read no insert locks that are timed.',
  `MAX_TIMER_READ_NO_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all internal read no insert locks that are timed.',
  `COUNT_READ_EXTERNAL` bigint(20) unsigned NOT NULL COMMENT 'Number of all external read locks.',
  `SUM_TIMER_READ_EXTERNAL` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all external read locks that are timed.',
  `MIN_TIMER_READ_EXTERNAL` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all external read locks that are timed.',
  `AVG_TIMER_READ_EXTERNAL` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all external read locks that are timed.',
  `MAX_TIMER_READ_EXTERNAL` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all external read locks that are timed.',
  `COUNT_WRITE_ALLOW_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Number of all internal read normal locks.',
  `SUM_TIMER_WRITE_ALLOW_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all internal write allow write locks that are timed.',
  `MIN_TIMER_WRITE_ALLOW_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all internal write allow write locks that are timed.',
  `AVG_TIMER_WRITE_ALLOW_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all internal write allow write locks that are timed.',
  `MAX_TIMER_WRITE_ALLOW_WRITE` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all internal write allow write locks that are timed.',
  `COUNT_WRITE_CONCURRENT_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Number of all internal concurrent insert write locks.',
  `SUM_TIMER_WRITE_CONCURRENT_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all internal concurrent insert write locks that are timed.',
  `MIN_TIMER_WRITE_CONCURRENT_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all internal concurrent insert write locks that are timed.',
  `AVG_TIMER_WRITE_CONCURRENT_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all internal concurrent insert write locks that are timed.',
  `MAX_TIMER_WRITE_CONCURRENT_INSERT` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all internal concurrent insert write locks that are timed.',
  `COUNT_WRITE_DELAYED` bigint(20) unsigned NOT NULL COMMENT 'Number of all internal write delayed locks.',
  `SUM_TIMER_WRITE_DELAYED` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all internal write delayed locks that are timed.',
  `MIN_TIMER_WRITE_DELAYED` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all internal write delayed locks that are timed.',
  `AVG_TIMER_WRITE_DELAYED` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all internal write delayed locks that are timed.',
  `MAX_TIMER_WRITE_DELAYED` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all internal write delayed locks that are timed.',
  `COUNT_WRITE_LOW_PRIORITY` bigint(20) unsigned NOT NULL COMMENT 'Number of all internal write low priority locks.',
  `SUM_TIMER_WRITE_LOW_PRIORITY` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all internal write low priority locks that are timed.',
  `MIN_TIMER_WRITE_LOW_PRIORITY` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all internal write low priority locks that are timed.',
  `AVG_TIMER_WRITE_LOW_PRIORITY` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all internal write low priority locks that are timed.',
  `MAX_TIMER_WRITE_LOW_PRIORITY` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all internal write low priority locks that are timed.',
  `COUNT_WRITE_NORMAL` bigint(20) unsigned NOT NULL COMMENT 'Number of all internal write normal locks.',
  `SUM_TIMER_WRITE_NORMAL` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all internal write normal locks that are timed.',
  `MIN_TIMER_WRITE_NORMAL` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all internal write normal locks that are timed.',
  `AVG_TIMER_WRITE_NORMAL` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all internal write normal locks that are timed.',
  `MAX_TIMER_WRITE_NORMAL` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all internal write normal locks that are timed.',
  `COUNT_WRITE_EXTERNAL` bigint(20) unsigned NOT NULL COMMENT 'Number of all external write locks.',
  `SUM_TIMER_WRITE_EXTERNAL` bigint(20) unsigned NOT NULL COMMENT 'Total wait time of all external write locks that are timed.',
  `MIN_TIMER_WRITE_EXTERNAL` bigint(20) unsigned NOT NULL COMMENT 'Minimum wait time of all external write locks that are timed.',
  `AVG_TIMER_WRITE_EXTERNAL` bigint(20) unsigned NOT NULL COMMENT 'Average wait time of all external write locks that are timed.',
  `MAX_TIMER_WRITE_EXTERNAL` bigint(20) unsigned NOT NULL COMMENT 'Maximum wait time of all external write locks that are timed.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `table_lock_waits_summary_by_table`
--

LOCK TABLES `table_lock_waits_summary_by_table` WRITE;
/*!40000 ALTER TABLE `table_lock_waits_summary_by_table` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `table_lock_waits_summary_by_table` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `threads`
--

DROP TABLE IF EXISTS `threads`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `threads` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'A unique thread identifier.',
  `NAME` varchar(128) NOT NULL COMMENT 'Name associated with the server''s thread instrumentation code, for example thread/sql/main for the server''s main() function, and thread/sql/one_connection for a user connection.',
  `TYPE` varchar(10) NOT NULL COMMENT 'FOREGROUND or BACKGROUND, depending on the thread type. User connection threads are FOREGROUND, internal server threads are BACKGROUND.',
  `PROCESSLIST_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'The PROCESSLIST.ID value for threads displayed in the INFORMATION_SCHEMA.PROCESSLIST table, or 0 for background threads. Also corresponds with the CONNECTION_ID() return value for the thread.',
  `PROCESSLIST_USER` varchar(128) DEFAULT NULL COMMENT 'Foreground thread user, or NULL for a background thread.',
  `PROCESSLIST_HOST` varchar(255) DEFAULT NULL COMMENT 'Foreground thread host, or NULL for a background thread.',
  `PROCESSLIST_DB` varchar(64) DEFAULT NULL COMMENT 'Thread''s default database, or NULL if none exists.',
  `PROCESSLIST_COMMAND` varchar(16) DEFAULT NULL COMMENT 'Type of command executed by the thread. These correspond to the the COM_xxx client/server protocol commands, and the Com_xxx status variables. See Thread Command Values.',
  `PROCESSLIST_TIME` bigint(20) DEFAULT NULL COMMENT 'Time in seconds the thread has been in its current state.',
  `PROCESSLIST_STATE` varchar(64) DEFAULT NULL COMMENT 'Action, event or state indicating what the thread is doing.',
  `PROCESSLIST_INFO` longtext DEFAULT NULL COMMENT 'Statement being executed by the thread, or NULL if a statement is not being executed. If a statement results in calling other statements, such as for a stored procedure, the innermost statement from the stored procedure is shown here.',
  `PARENT_THREAD_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'THREAD_ID of the parent thread, if any. Subthreads can for example be spawned as a result of INSERT DELAYED statements.',
  `ROLE` varchar(64) DEFAULT NULL COMMENT 'Unused.',
  `INSTRUMENTED` enum('YES','NO') NOT NULL COMMENT 'YES or NO for Whether the thread is instrumented or not. For foreground threads, the initial value is determined by whether there''s a user/host match in the setup_actors table. Subthreads are again matched, while for background threads, this will be set to YES by default. To monitor events that the thread executes, INSTRUMENTED must be YES and the thread_instrumentation consumer in the setup_consumers table must also be YES.',
  `HISTORY` enum('YES','NO') NOT NULL COMMENT 'Whether to log historical events for the thread.',
  `CONNECTION_TYPE` varchar(16) DEFAULT NULL COMMENT 'The protocol used to establish the connection, or NULL for background threads.',
  `THREAD_OS_ID` bigint(20) unsigned DEFAULT NULL COMMENT 'The thread or task identifier as defined by the underlying operating system, if there is one.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `threads`
--

LOCK TABLES `threads` WRITE;
/*!40000 ALTER TABLE `threads` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `threads` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `user_variables_by_thread`
--

DROP TABLE IF EXISTS `user_variables_by_thread`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `user_variables_by_thread` (
  `THREAD_ID` bigint(20) unsigned NOT NULL COMMENT 'The thread identifier of the session in which the variable is defined.',
  `VARIABLE_NAME` varchar(64) NOT NULL COMMENT 'The variable name, without the leading @ character.',
  `VARIABLE_VALUE` longblob DEFAULT NULL COMMENT 'The variable value'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_variables_by_thread`
--

LOCK TABLES `user_variables_by_thread` WRITE;
/*!40000 ALTER TABLE `user_variables_by_thread` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `user_variables_by_thread` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `USER` char(128) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT 'The connection''s client user name for the connection, or NULL if an internal thread.',
  `CURRENT_CONNECTIONS` bigint(20) NOT NULL COMMENT 'Current connections for the user.',
  `TOTAL_CONNECTIONS` bigint(20) NOT NULL COMMENT 'Total connections for the user.'
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Dumping routines for database 'performance_schema'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*M!100616 SET NOTE_VERBOSITY=@OLD_NOTE_VERBOSITY */;

-- Dump completed on 2025-06-13 22:30:45
