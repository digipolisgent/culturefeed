<?php

/**
 * @file
 * Contains \Drupal\culturefeed_udb3\Entity\DomainMessageEntity.
 */

namespace Drupal\culturefeed_udb3\Entity;

use Drupal\Core\Entity\ContentEntityBase;
use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\Core\Entity\EntityTypeInterface;
use Drupal\Core\Field\BaseFieldDefinition;

/**
 * Defines the culturefeed user entity.
 *
 * @ContentEntityType(
 *   id = "culturefeed_domain_message",
 *   label = @Translation("Culturefeed domain message"),
 *   base_table = "culturefeed_domain_message",
 *   handlers = {
 *     "storage_schema" = "Drupal\culturefeed_udb3\DomainMessageStorageSchema",
 *   },
 *   entity_keys = {
 *     "id" = "dmid",
 *   },
 *   fieldable = FALSE,
 * )
 */
class DomainMessageEntity extends ContentEntityBase implements ContentEntityInterface {

  /**
   * {@inheritdoc}
   */
  public static function baseFieldDefinitions(EntityTypeInterface $entity_type) {

    $fields['dmid'] = BaseFieldDefinition::create('integer')
      ->setLabel(t('ID'))
      ->setDescription(t('ID.'))
      ->setReadOnly(TRUE);

    $fields['uuid'] = BaseFieldDefinition::create('string')
      ->setLabel(t('UUID'))
      ->setDescription(t('UUID.'));

    $fields['playhead'] = BaseFieldDefinition::create('integer')
      ->setLabel(t('Playhead'))
      ->setDescription(t('Playhead.'))
      ->setSetting('unsigned', TRUE);

    $fields['metadata'] = BaseFieldDefinition::create('string_long')
      ->setLabel(t('Metadata'))
      ->setDescription(t('Metadata.'));

    $fields['payload'] = BaseFieldDefinition::create('string_long')
      ->setLabel(t('Payload'))
      ->setDescription(t('Payload.'));

    $fields['recorded_on'] = BaseFieldDefinition::create('string')
      ->setLabel(t('Recorded on'))
      ->setDescription(t('Recorded on.'));

    $fields['type'] = BaseFieldDefinition::create('string')
      ->setLabel(t('Type'))
      ->setDescription(t('Type.'));

    return $fields;

  }

}