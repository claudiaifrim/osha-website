<?php
/**
 * Imports advisory groups exported from CRM to XML files on disk.
 *
 * The data is stored inside the press_contact
 */
class MigrateOshaAdvisoryGroups extends OSHADynamicMigration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct(MigrateGroup::getInstance('OSHA Content types'));
    $this->description = 'Import advisory groups from CRM XML file';

    $root_dir = $arguments['root_dir'];
    $prag_xml = $root_dir . '/AdvisoryGroupsPRAG.xml';
    $agcp_xml = $root_dir . '/AdvisoryGroupsAGCP.xml';

    $this->source = new MigrateSourceList(
      new AdvisoryGroupsMigrateList($prag_xml, $agcp_xml),
      new AdvisoryGroupMigrateItem(),
      $this->fields()
    );

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'varchar',
          'length' => 200,
          'not null' => TRUE,
          'description' => 'Person full name',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $node_options = MigrateDestinationNode::options('en', 'full_html');
    $this->destination = new MigrateDestinationNode('press_contact', $node_options);

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('field_personal_title', 'field_personal_title');
    $this->addFieldMapping('title_field', 'title_field');

    $this->addFieldMapping('field_wg_role_1', 'field_wg_role_1');
    $this->addFieldMapping('field_wg_role_1:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_wg_role_1:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_wg_role_2', 'field_wg_role_2');
    $this->addFieldMapping('field_wg_role_2:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_wg_role_2:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_wg_category', 'field_wg_category');
    $this->addFieldMapping('field_wg_category:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_wg_category:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_press_contact_organization', 'field_press_contact_organization');
    $this->addFieldMapping('field_press_contact_location', 'field_press_contact_location');
    $this->addFieldMapping('field_city', 'field_city');
    $this->addFieldMapping('field_zip_code', 'field_zip_code');
    $this->addFieldMapping('field_is_advisory', 'field_is_advisory');

    $this->addFieldMapping('field_contact_uuid', 'field_contact_uuid');

    $this->addFieldMapping('field_contact_type', 'field_contact_type');
    $this->addFieldMapping('field_contact_type:create_term')->defaultValue(TRUE);

    $this->addFieldMapping('field_press_contact_cv', 'field_press_contact_cv');
    $this->addFieldMapping('field_press_contact_declaration', 'field_press_contact_declaration');
    $this->addFieldMapping('uid')->defaultValue(1);

    $this->addFieldMapping('field_country', 'field_country_iso2');
    $this->addFieldMapping('field_country:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_country:create_term')->defaultValue(FALSE);

    $this->addUnmigratedDestinations(array(
      'created', 'changed', 'status', 'promote', 'sticky', 'revision', 'log',
      'language', 'tnid', 'translate', 'revision_uid', 'is_new',
      'field_press_contact_email',
      'field_press_contact_job_title',
      'field_press_contact_job_title:language',
      'field_press_contact_location:language',
      'field_press_contact_organization:language',
      'field_press_contact_phone',
      'field_press_contact_phone:language',
      'title_field:language',
      'field_city:language',
      'field_contact_type:source_type',
      'field_personal_title:language',
      'field_country:ignore_case',
      'field_wg_category:source_type',
      'field_wg_role_1:source_type',
      'field_wg_role_2:source_type',
      'field_zip_code:language',
      'field_website',
      'field_website:title',
      'field_website:attributes',
      'field_website:language',
      'field_contact_uuid:language',

      'field_press_contact_cv:file_class',
      'field_press_contact_cv:language',
      'field_press_contact_cv:destination_dir',
      'field_press_contact_cv:destination_file',
      'field_press_contact_cv:file_replace',
      'field_press_contact_cv:preserve_files',
      'field_press_contact_cv:source_dir',
      'field_press_contact_cv:description',
      'field_press_contact_cv:display',

      'field_press_contact_declaration:file_class',
      'field_press_contact_declaration:language',
      'field_press_contact_declaration:destination_dir',
      'field_press_contact_declaration:destination_file',
      'field_press_contact_declaration:file_replace',
      'field_press_contact_declaration:preserve_files',
      'field_press_contact_declaration:source_dir',
      'field_press_contact_declaration:description',
      'field_press_contact_declaration:display',

      'path',
      'metatag_title',
      'metatag_description',
      'metatag_abstract',
      'metatag_keywords',
      'metatag_robots',
      'metatag_news_keywords',
      'metatag_standout',
      'metatag_generator',
      'metatag_rights',
      'metatag_image_src',
      'metatag_canonical',
      'metatag_shortlink',
      'metatag_publisher',
      'metatag_author',
      'metatag_original-source',
      'metatag_revisit-after',
      'metatag_content-language',
      'metatag_dcterms.title',
      'metatag_dcterms.creator',
      'metatag_dcterms.subject',
      'metatag_dcterms.description',
      'metatag_dcterms.publisher',
      'metatag_dcterms.contributor',
      'metatag_dcterms.date',
      'metatag_dcterms.modified',
      'metatag_dcterms.type',
      'metatag_dcterms.format',
      'metatag_dcterms.identifier',
      'metatag_dcterms.source',
      'metatag_dcterms.language',
      'metatag_dcterms.relation',
      'metatag_dcterms.coverage',
      'metatag_dcterms.rights',
      'comment',
    ));
  }

  /**
   * Migration machine name.
   *
   * {@inheritdoc}
   */
  protected function generateMachineName() {
    return OSHA_MIGRATION_CONTENT_ADVISORY_GROUPS;
  }

  /**
   * Prepare raw data pulled from source.
   *
   * {@inheritdoc}
   */
  public function prepareRow($row) {
    if (empty($row->field_contact_uuid)) {
      $this->saveMessage('Skipping contact without uuid', MigrationBase::MESSAGE_WARNING);
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Called by destination right before saving.
   *
   * @param object $entity
   *   Entity to save
   * @param object $row
   *   Source row
   */
  public function prepare($entity, $row) {
    $entity->path['pathauto'] = 0;
    $tid = MigrationUtil::getCountryTermByISO2($row->field_country_iso2);
    if (empty($tid)) {
      $this->displayMessage('Advisory member ' . $row->title . ' - country ' . $row->field_country_iso2 . ' not found', 'warning');
      $row->field_country_iso2 = NULL;
    }
    else {
      $entity->field_country[LANGUAGE_NONE][0] = array('tid' => $tid);
    }
    // Save the CV file to disk.
    if (!empty($row->field_press_contact_cv)) {
      $files_dir = 'public://contact_cv';
      if (file_prepare_directory($files_dir, FILE_CREATE_DIRECTORY)) {
        $destination = 'public://contact_cv/' . $row->id . '_' . $row->field_press_contact_cv['filename'];
        $binary_data = base64_decode($row->field_press_contact_cv['content']);
        if ($file = file_save_data($binary_data, $destination, FILE_EXISTS_OVERWRITE)) {
          $file->display = 1;
          $entity->field_press_contact_cv[LANGUAGE_NONE][0] = (array)$file;
        }
      }
    }

    // Save the declaration of interests on disk.
    if (!empty($row->field_press_contact_declaration)) {
      $files_dir = 'public://contacts_declarations';
      if (file_prepare_directory($files_dir, FILE_CREATE_DIRECTORY)) {
        $destination = 'public://contacts_declarations/' . $row->id . '_' . $row->field_press_contact_declaration['filename'];
        $binary_data = base64_decode($row->field_press_contact_declaration['content']);
        if ($file = file_save_data($binary_data, $destination, FILE_EXISTS_OVERWRITE)) {
          $file->display = 1;
          $entity->field_press_contact_declaration[LANGUAGE_NONE][0] = (array) $file;
        }
      }
    }
  }

  public function complete($entity, $row) {
  }

  /**
   * Executes after import.
   */
  public function postImport() {
    parent::postImport();
    $this->removeNeedsUpdateItems();
  }

  /**
   * Return the list of available source fields.
   *
   * @return array
   *   An array o fields with their description
   */
  public function fields() {
    return array(
      'id' => 'Primary Key (URL pattern)',
      'title' => '',
      'title_field' => '',
      'field_personal_title' => '',
      'field_wg_role_1' => '',
      'field_wg_role_2' => '',
      'field_wg_category' => '',
      'field_press_contact_organization' => '',
      'field_press_contact_location' => '',
      'field_country_iso2' => '',
      'field_zip_code' => '',
      'field_city' => '',
      'field_contact_uuid' => '',
      'field_contact_type' => '',
      'field_press_contact_declaration' => '',
      'field_press_contact_cv' => '',
    );
  }
}


class AdvisoryGroupsMigrateList extends MigrateList {

  public static $data = array();

  protected $prag_xml = NULL;
  protected $agcp_xml = NULl;


  /**
   * {@inheritdoc}
   */
  public function __construct($prag_xml, $agcp_xml) {
    parent::__construct();
    $this->prag_xml = $prag_xml;
    $this->agcp_xml = $agcp_xml;
    $this->parseSourceFiles();
  }

  /**
   * {@inheritdoc}
   */
  public function __toString() {
    return OSHA_MIGRATION_CONTENT_ADVISORY_GROUPS;
  }

  protected function parseSourceFiles() {
    $prag = $this->parseXMLFile($this->prag_xml, 'Prevention and Research Advisory Group', 'prag');
    $agcp = $this->parseXMLFile($this->agcp_xml, 'Advisory Group on Communication & Promotion', 'agcp');
    // Both XML files are migrated as separate records (even if people are duplicate)
    self::$data = array_merge($prag, $agcp);
  }

  /**
   * Parse the XML file and populate the local cache.
   */
  protected function parseXMLFile($file, $type, $type_identifier) {
    $rows = array();
    if (!is_readable($file)) {
      // The file might end with .XML
      $new_file = str_replace('.xml', '.XML', $file);
      if (!is_readable($new_file)) {
        return $rows;
      }
      else {
        $file = $new_file;
      }
    }
    if ($xml = simplexml_load_file($file, 'SimpleXMLElement', LIBXML_COMPACT | LIBXML_PARSEHUGE)) {
      $title = $xml->xpath('//Table0_Group0_Header0/Table0_Group0_Header0');
      $title = (string) $title[0];
      if (!empty($title)) {
        $type = $title;
      }
      foreach ($xml->xpath('//Detail') as $member) {
        $data = new stdClass();
        $attributes = $member->attributes();
        $data->title = (string) $attributes['Table0_Details4'];
        //$id = $type_identifier . '-' . strtolower(str_replace(' ', '-', $data->title));
        $data->field_contact_uuid = (string) $attributes['Textbox8'];
        $id = $type_identifier . '-' . $data->field_contact_uuid;
        $data->title_field = (string) $attributes['Table0_Details4'];
        $data->field_personal_title = (string) $attributes['Table0_Details3'];
        $data->field_wg_role_1 = (string) $attributes['Table0_Details2'];
        $data->field_wg_role_2 = (string) $attributes['Table0_Details5'];
        $data->field_wg_category = (string) $attributes['Table0_Details1'];
        $data->field_press_contact_organization = (string) $attributes['Table0_Details6'];
        $data->field_press_contact_location = (string) $attributes['Table0_Details7'];
        $data->field_country_iso2 = (string) $attributes['Textbox9'];
        $data->field_zip_code = (string) $attributes['Textbox1'];
        $data->field_city = (string) $attributes['Textbox4'];
        $data->field_contact_type[] = $type;
        $data->field_is_advisory = TRUE;
        $attached_pdfs = $member->xpath('AttachedPDFs');
        $attached_pdfs = current($attached_pdfs);
        foreach ($attached_pdfs->xpath('File') as $file_xml) {
          $file_attr = $file_xml->attributes();
          $file_content = (string) $file_xml->Content;
          $destination = (string) $file_attr['Filename'];
          if (!empty($file_content) && !empty($destination)) {
            if ((string) $file_attr['DocumentType'] == 'CV') {
              $data->field_press_contact_cv = array(
                'content' => $file_content,
                'filename' => $destination,
              );
            }
            else {
              $data->field_press_contact_declaration = array(
                'content' => $file_content,
                'filename' => $destination,
              );
            }
          }
        }
        $rows[$id] = $data;
      }
    }
    return $rows;
  }

  /**
   * {@inheritdoc}
   */
  public function getIdList() {
    if (empty(self::$data)) {
      $this->parseSourceFiles();
    }
    return array_keys(self::$data);
  }

  /**
   * {@inheritdoc}
   */
  public function computeCount() {
    return count(self::$data);
  }
}

class AdvisoryGroupMigrateItem extends MigrateItem {

  /**
   * {@inheritdoc}
   */
  public function getItem($item_id) {
    if (array_key_exists($item_id, AdvisoryGroupsMigrateList::$data)) {
      return (object) AdvisoryGroupsMigrateList::$data[$item_id];
    }
    return NULL;
  }
}
